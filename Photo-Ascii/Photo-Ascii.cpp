#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool status = false;

char AsciiMap(unsigned char grayValue) {

	const std::string ascii_chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

	int index = grayValue * (ascii_chars.length() - 1) / 255;
	
	return ascii_chars[index];

}

std::string generateAscii(unsigned char* gray, int width, int height, float outputWidth) {
	float scaleX = width / outputWidth;
	float scaleY = scaleX * 1.8;

	float outputHeight = height / scaleY;

	std::string ascii; //string z obrazem

	for (int outY = 0; outY < outputHeight; outY++) {
		for (int outX = 0; outX < outputWidth; outX++) {
			int origX = outX * scaleX;
			int origY = outY * scaleY;
			int licznik = 0;
			int suma = 0;

			int endX = std::min(origX + static_cast<int>(scaleX), width);
			int endY = std::min(origY + static_cast<int>(scaleY), height);

			for (int i = origX; i < endX; i++) {
				for (int j = origY; j < endY; j++) {
					suma += gray[j * width + i];
					licznik++;
				}
			}

			suma = suma / licznik;

			ascii += AsciiMap(suma);
		}
		ascii += '\n';
	}

	
	status = true;
	return ascii;
}

void saveFile(bool status, std::string ascii) {

	std::string fileName = "AsciiArt.txt";

	if (status == true) {

		std::cout << "Podaj nazwe pliku do jakiego zapisac obraz (Podstawowo AsciiArt.txt) : ";
		std::string input;
		std::getline(std::cin, input);


		if (!input.empty()) {
			fileName = input;
		}

		std::ofstream file(fileName);

		if (file.is_open()) {
			file << ascii;
			file.close();
		}

	}
	else {
		std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
	}
}

int main()
{

	int width, height, channels;
	unsigned char* img = stbi_load("zdjecie.jpg", &width, &height, &channels, 3); //wymusznie 3 kanalow RGB

	int outputWidth = 120; //dokladnos - wielkosc 


	if (img){
		std::cout << "Zladowano zdj" << std::endl;
		std::cout << "Podaj dokladnosc generowania (Podstawowo 120) : ";
		
		std::string input;
		std::getline(std::cin, input);

		if (!input.empty())
		{
			try
			{
				outputWidth = std::stoi(input);
			}
			catch (...)
			{
				std::cout << "Niepoprawna liczba. Uzywam wartosci domyslnej (120).\n";
			}
		}
	}
	else {
		std::cout << "Blad ladowania zdj" << std::endl;
		std::cout << "Blad: " << stbi_failure_reason() << std::endl;
		return 1;
	}

	int desiredChannels = 3;
	unsigned char* gray = new unsigned char[width * height]; //tablica na wartosci szarosci

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) {

			int pixelIndex = (y * width + x) * desiredChannels;

			unsigned char r = img[pixelIndex + 0];
			unsigned char g = img[pixelIndex + 1];
			unsigned char b = img[pixelIndex + 2];

			//standardowy wzor na luminancje
			unsigned char grayValue = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);

			gray[y * width + x] = grayValue;

		}
	}

	std::string ascii = generateAscii(gray, width, height, outputWidth);
	std::cout << ascii;

	std::cout << "Czy chcesz zapisac obraz do pliku ? (T/N): ";
	std::string input;
	std::getline(std::cin, input);


	if (input == "T" || input == "t") {
		saveFile(status, ascii);
	}
	else if (input == "N" || input == "n"){
		std::cout << "Nie zapisuje pliku";
	}
	else {
		std::cout << "Nie wlasciwa odpowedz! Nie zapisuje pliku";
	}


	stbi_image_free(img);
	delete[] gray;

}

