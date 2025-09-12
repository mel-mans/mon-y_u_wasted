#include <iostream>
#include <filesystem>
#include <regex>
#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;

bool isImageFile(const fs::path& path) {
    std::string ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp" || ext == ".tif";
}

double extractSumFromText(const std::string& text) {
    std::regex decimalRegex(R"((\d+\.\d+))");
    std::sregex_iterator begin(text.begin(), text.end(), decimalRegex), end;
    double sum = 0.0;
    for (auto it = begin; it != end; ++it) {
        sum += std::stod(it->str());
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./ocr_sum <folder_path>" << std::endl;
        return 1;
    }

    std::string folderPath = argv[1];
    double totalSum = 0.0;

    tesseract::TessBaseAPI tess;
    if (tess.Init(NULL, "eng")) {
        std::cerr << "Could not initialize tesseract.\n";
        return 1;
    }

    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (!entry.is_regular_file() || !isImageFile(entry.path()))
            continue;

        std::cout << "Processing: " << entry.path() << std::endl;

        cv::Mat image = cv::imread(entry.path().string(), cv::IMREAD_COLOR);
        if (image.empty()) {
            std::cerr << "Failed to load image: " << entry.path() << std::endl;
            continue;
        }

        tess.SetImage(image.data, image.cols, image.rows, image.elemSize(), image.step);
        char* outText = tess.GetUTF8Text();
        if (!outText) {
            std::cerr << "OCR failed for: " << entry.path() << std::endl;
            continue;
        }

        double sum = extractSumFromText(outText);
        totalSum += sum;
    }

    if (totalSum >= 10000)
    	std::cout << "\nWalmlayen mshaw a s7aybi: " << totalSum << "dh" << std::endl;
    else
    	std::cout << "\nHash7al khssrti: " << totalSum << "dh" << std::endl;
    tess.End();
    return 0;
}

