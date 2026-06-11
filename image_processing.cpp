#include "image_processing.h"

using namespace cv;

// ---------------------------------------------------------------------
// Filtro 1: Remoção de ruído
// ---------------------------------------------------------------------
Mat ImageProcessor::removeNoise(const Mat& image)
{
    Mat result;

    fastNlMeansDenoisingColored(
        image,
        result,
        10, // intensidade luminância
        10, // intensidade cor
        7,
        21
    );

    return result;
}

// ---------------------------------------------------------------------
// Filtro 2: Melhoria de contraste usando CLAHE
// ---------------------------------------------------------------------
Mat ImageProcessor::enhanceContrast(const Mat& image)
{
    Mat lab;
    cvtColor(image, lab, COLOR_BGR2Lab);

    std::vector<Mat> channels;
    split(lab, channels);

    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(3.0);

    clahe->apply(channels[0], channels[0]);

    merge(channels, lab);

    Mat result;
    cvtColor(lab, result, COLOR_Lab2BGR);

    return result;
}

// ---------------------------------------------------------------------
// Filtro 3: Nitidez (Sharpen)
// ---------------------------------------------------------------------
Mat ImageProcessor::sharpenImage(const Mat& image)
{
    Mat result;

    Mat kernel = (Mat_<float>(3,3) <<
         0, -1,  0,
        -1,  5, -1,
         0, -1,  0);

    filter2D(image, result, image.depth(), kernel);

    return result;
}

// ---------------------------------------------------------------------
// Simulação de digitalização da página
// ---------------------------------------------------------------------
Mat ImageProcessor::scanDocument(const Mat& image)
{
    Mat gray;
    Mat scanned;

    cvtColor(image, gray, COLOR_BGR2GRAY);

    adaptiveThreshold(
        gray,
        scanned,
        255,
        ADAPTIVE_THRESH_GAUSSIAN_C,
        THRESH_BINARY,
        31,
        15
    );

    return scanned;
}

// ---------------------------------------------------------------------
// Pipeline completo
// ---------------------------------------------------------------------
bool ImageProcessor::processImage(
    const std::string& inputPath,
    const std::string& outputPath)
{
    Mat image = imread(inputPath);

    if (image.empty())
    {
        return false;
    }

    Mat denoised = removeNoise(image);

    Mat contrast = enhanceContrast(denoised);

    Mat sharpened = sharpenImage(contrast);

    Mat scanned = scanDocument(sharpened);

    imwrite(outputPath, scanned);

    return true;
}
