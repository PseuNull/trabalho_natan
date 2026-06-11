#include <iostream>
#include "image_processing.h"

int main()
{
    std::string inputImage;
    std::string outputImage;

    std::cout << "Digite o caminho da imagem: ";
    std::getline(std::cin, inputImage);

    std::cout << "Digite o nome da imagem de saída: ";
    std::getline(std::cin, outputImage);

    ImageProcessor processor;

    if(processor.processImage(inputImage, outputImage))
    {
        std::cout << "Imagem restaurada e digitalizada com sucesso!"
                  << std::endl;
    }
    else
    {
        std::cout << "Erro ao carregar a imagem."
                  << std::endl;
    }

    return 0;
}
