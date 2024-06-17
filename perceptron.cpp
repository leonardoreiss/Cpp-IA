#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib> // for std::rand and std::srand
#include <ctime>   // for std::time

using namespace std;

// Classe Perceptron
class Perceptron {
private:
    vector<double> weights;  // Vetor de pesos
    double learning_rate;    // Taxa de aprendizagem
    bool use_bias;           // Flag para utilizar bias
    int num_iterations;      // Número de iterações até convergência

public:
    // Construtor
    Perceptron(bool use_bias_flag, double learning_rate_val) {
        use_bias = use_bias_flag;
        learning_rate = learning_rate_val;
        num_iterations = 0;
    }

    // Função para treinar o Perceptron
    void train(vector<vector<double>>& inputs, vector<double>& expected_outputs) {
        // Inicialização dos pesos com valores aleatórios entre -1 e 1
        initialize_weights(inputs[0].size() + (use_bias ? 1 : 0));

        bool converged = false;
        int max_iterations = 1000; // Limite máximo de iterações para evitar loop infinito
        while (!converged && num_iterations < max_iterations) {
            converged = true;
            for (size_t i = 0; i < inputs.size(); ++i) {
                double predicted_output = calculate_output(inputs[i]);
                double error = expected_outputs[i] - predicted_output;
                if (abs(error) > 1e-6) { // Se houver erro
                    update_weights(inputs[i], error);
                    converged = false; // Continua treinando
                }
            }
            num_iterations++;
        }
    }

    // Função para inicializar os pesos com valores aleatórios entre -1 e 1
    void initialize_weights(size_t num_weights) {
        weights.resize(num_weights);
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Inicializa a semente do gerador randômico
        for (size_t i = 0; i < num_weights; ++i) {
            weights[i] = (std::rand() / (double)RAND_MAX) * 2 - 1; // Gera valor entre -1 e 1
        }
    }

    // Função para calcular a saída do Perceptron para uma entrada dada
    double calculate_output(vector<double>& input) {
        double output = 0.0;
        for (size_t i = 0; i < input.size(); ++i) {
            output += weights[i] * input[i];
        }
        if (use_bias) {
            output += weights.back(); // Último peso é o bias
        }
        return activation_function(output); // Aplica a função de ativação
    }

    // Função de ativação simples (degrau)
    double activation_function(double value) {
        return (value >= 0) ? 1.0 : 0.0;
    }

    // Função para atualizar os pesos
    void update_weights(vector<double>& input, double error) {
        for (size_t i = 0; i < input.size(); ++i) {
            weights[i] += learning_rate * error * input[i];
        }
        if (use_bias) {
            weights.back() += learning_rate * error; // Atualiza o bias
        }
    }

    // Função para obter os pesos aprendidos
    vector<double>& get_weights() {
        return weights;
    }

    // Função para obter o número de iterações necessárias para o aprendizado
    int get_num_iterations() {
        return num_iterations;
    }
};

// Função para ler entradas do usuário
void read_user_input(vector<vector<double>>& inputs, vector<double>& expected_outputs) {
    int num_training_examples = 3;
    inputs.resize(num_training_examples);
    expected_outputs.resize(num_training_examples);

    cout << "Entre com os pares de valores x1, x2 e x3 e seus respectivos valores yk esperados:" << endl;
    for (int i = 0; i < num_training_examples; ++i) {
        double x1, x2, x3, yk;
        cout << "Exemplo " << i + 1 << ": ";
        cin >> x1 >> x2 >> x3 >> yk;
        inputs[i] = {x1, x2, x3};
        expected_outputs[i] = yk;
    }
}

int main() {
    // Leitura de entradas do usuário
    vector<vector<double>> inputs;
    vector<double> expected_outputs;
    read_user_input(inputs, expected_outputs);

    // Parâmetros escolhidos pelo usuário
    bool use_bias;
    double learning_rate;
    cout << "Deseja utilizar bias? (1 para Sim, 0 para Não): ";
    cin >> use_bias;
    cout << "Entre com a taxa de aprendizagem: ";
    cin >> learning_rate;

    // Criando e treinando o Perceptron
    Perceptron perceptron(use_bias, learning_rate);
    perceptron.train(inputs, expected_outputs);

    // Exibindo os pesos aprendidos e o número de iterações necessárias
    vector<double> learned_weights = perceptron.get_weights();
    int iterations = perceptron.get_num_iterations();

    cout << "\nPesos aprendidos:";
    for (size_t i = 0; i < learned_weights.size(); ++i) {
        cout << " " << learned_weights[i];
    }
    cout << endl;
    cout << "Número de iterações: " << iterations << endl;

    // Loop para testar com novos valores de entrada
    char test_choice = 's';
    while (test_choice == 's' || test_choice == 'S') {
        vector<double> new_input(3);
        cout << "\nEntre com os novos valores de entrada (x1, x2, x3): ";
        cin >> new_input[0] >> new_input[1] >> new_input[2];
        double predicted_output = perceptron.calculate_output(new_input);
        cout << "Saída prevista: " << predicted_output << endl;

        cout << "\nDeseja testar com mais novos valores de entrada? (s/n): ";
        cin >> test_choice;
    }

    return 0;
}
