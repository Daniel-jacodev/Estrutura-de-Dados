#include <iostream>
#include <string>
#include <stdexcept> // Para usar std::runtime_error

// Definindo um enum class para os dias da semana
enum class DiaDaSemana {
    Domingo,
    Segunda,
    Terca,
    Quarta,
    Quinta,
    Sexta,
    Sabado
};

// Função para converter DiaDaSemana para string
std::string diaToString(DiaDaSemana dia) {
    switch (dia) {
        case DiaDaSemana::Domingo: return "Domingo";
        case DiaDaSemana::Segunda: return "Segunda";
        case DiaDaSemana::Terca:   return "Terça";
        case DiaDaSemana::Quarta:  return "Quarta";
        case DiaDaSemana::Quinta:  return "Quinta";
        case DiaDaSemana::Sexta:   return "Sexta";
        case DiaDaSemana::Sabado:  return "Sábado";
        default: throw std::runtime_error("Dia inválido");
    }
}

// Função para converter string para DiaDaSemana
DiaDaSemana stringToDia(const std::string& str) {
    if (str == "Domingo") return DiaDaSemana::Domingo;
    if (str == "Segunda") return DiaDaSemana::Segunda;
    if (str == "Terça")   return DiaDaSemana::Terca;
    if (str == "Quarta")  return DiaDaSemana::Quarta;
    if (str == "Quinta")  return DiaDaSemana::Quinta;
    if (str == "Sexta")   return DiaDaSemana::Sexta;
    if (str == "Sábado")  return DiaDaSemana::Sabado;
    throw std::runtime_error("String inválida para DiaDaSemana");
}

int main() {
    // Exemplo de uso
    DiaDaSemana hoje = DiaDaSemana::Terca;

    // Convertendo enum para string
    std::cout << "Hoje é: " << diaToString(hoje) << std::endl;

    // Convertendo string para enum
    std::string diaStr = "Sexta";
    DiaDaSemana outroDia = stringToDia(diaStr);
    std::cout << "Outro dia é: " << diaToString(outroDia) << std::endl;

    // Tentativa de conversão com string inválida (isso lançará uma exceção).
    try {
        DiaDaSemana diaInvalido = stringToDia("DiaErrado");
    } catch (const std::runtime_error& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }

    return 0;
}