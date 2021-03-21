#include <cmath>
#include <iostream>

void swap(long *sBlock, long firstIndex, long secondIndex);
long *processKeysMessageXorOperation(long *message, long messageLength, long *keyWords);
long *processPseudoRandomGenerationAlgorithm(long messageLength, long *sBlock, long sBlockLength);
void processKeySchedulingAlgorithm(long *sBlock, long sBlockLength, const long *key, long keyLength);

int main() {
    std::cout << "Добро пожаловать в мир CR4!" << std::endl << std::endl;
    std::cout << "Введите размер слова для алгоритма:" << std::endl;

    long n;
    std::cin >> n;

    long sBlockLength = pow(2, n);
    std::cout << "Длина S-блока: " << sBlockLength << std::endl;

    long *sBlock = new long[sBlockLength];

    std::cout << "Введите ключ для работы алгоритма:" << std::endl;
    std::cin.ignore();

    std::string inputKey;
    std::getline(std::cin, inputKey);

    long keyLength = inputKey.length();

    long *key = new long[keyLength];
    for (int i = 0; i < keyLength; i++) {
        key[i] = inputKey[i];
    }

    std::cout << "Введите сообщение для шифрования:" << std::endl;

    std::string inputMessage;
    std::getline(std::cin, inputMessage);

    long messageLength = inputMessage.length();

    std::cout << "Шифруемое сообщение: ";
    long *message = new long[messageLength];
    for (int i = 0; i < messageLength; i++) {
        message[i] = inputMessage[i];

        std::cout << inputMessage[i];
    }

    std::cout << std::endl;

    processKeySchedulingAlgorithm(sBlock, sBlockLength, key, keyLength);
    long *keyWords = processPseudoRandomGenerationAlgorithm(messageLength, sBlock, sBlockLength);

    long* encryptedMessage = processKeysMessageXorOperation(message, messageLength, keyWords);

    std::cout << "Зашифрованное сообщение: ";
    for (int i = 0; i < messageLength; i++) {
        std::cout << (char) encryptedMessage[i];
    }

    std::cout << std::endl;

    long* decryptedMessage = processKeysMessageXorOperation(encryptedMessage, messageLength, keyWords);

    std::cout << "Расшифрованное сообщение: ";
    for (int i = 0; i < messageLength; i++) {
        std::cout << (char) decryptedMessage[i];
    }

    std::cout << std::endl;

    return 0;
}

void swap(long *sBlock, long firstIndex, long secondIndex) {
    long temp = sBlock[firstIndex];
    sBlock[firstIndex] = sBlock[secondIndex];
    sBlock[secondIndex] = temp;
}

long *processKeysMessageXorOperation(long *message, long messageLength, long *keyWords) {
    long *encryptedMessage = new long[messageLength];

    for (int i = 0; i < messageLength; i++) {
        encryptedMessage[i] = keyWords[i] ^ message[i];
    }

    return encryptedMessage;
}

long *processPseudoRandomGenerationAlgorithm(long messageLength, long *sBlock, long sBlockLength) {
    long i = 0;
    long j = 0;

    long *keyWords = new long[messageLength];

    for (int k = 0; k < messageLength; k++) {
        i = (i + 1) % sBlockLength;
        j = (j + sBlock[i]) % sBlockLength;

        swap(sBlock, i, j);

        long keyWord = sBlock[(sBlock[i] + sBlock[j]) % sBlockLength];
        keyWords[k] = keyWord;
    }

    return keyWords;
}

void processKeySchedulingAlgorithm(long *sBlock, long sBlockLength, const long *key, long keyLength) {
    for (long i = 0; i < sBlockLength; i++) {
        sBlock[i] = i;
    }

    long j = 0;

    for (long i = 0; i < sBlockLength; i++) {
        j = (j + sBlock[i] + key[i % keyLength]) % sBlockLength;

        swap(sBlock, i, j);
    }
}
