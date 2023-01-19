#include <windows.h> // include la libreria per le funzioni di Windows
#include <Xinput.h> // include la libreria per le funzioni di Xinput
#include <iostream> // include la libreria per gli stream di input/output
#include <string> // include la libreria per le stringhe
#include <SerialStream.h> // include la libreria per la comunicazione seriale

using namespace std;

int main() {
    XINPUT_STATE state; // dichiarazione della struttura per salvare lo stato del controller
    int controllerId = 0; // id del controller connesso 
    string portName = "COM3"; // nome della porta seriale su cui l'arduino è connesso
    LibSerial::SerialStream arduino; //dichiarazione dell'oggetto arduino
    arduino.Open(portName); //apre la connessione seriale con arduino sulla porta specificata

    while (true) {
        ZeroMemory(&state, sizeof(XINPUT_STATE)); // azzera la memoria della struttura state
        XInputGetState(controllerId, &state); //ottieni lo stato del controller

        // Sterzo
        float x = (float)state.Gamepad.sThumbLX / 32767.0f; // converti in float tra -1 e 1
        // Acceleratore
        float y = (float)state.Gamepad.sThumbLY / -32767.0f; // converti in float tra 0 e 1
        // Freno
        float z = (float)state.Gamepad.sThumbRX / 32767.0f; // converti in float tra 0 e 1
        // Altri tasti
        int buttons = state.Gamepad.wButtons; // salva lo stato dei tasti

        // Invia i dati in formato seriale all'arduino
        arduino << x << "," << y << "," << z << "," << buttons << endl; // invia i dati al arduino 

        Sleep(100); // attende 100ms prima di ripetere il ciclo
    }

    arduino.Close(); // chiude la connessione seriale con arduino
    return 0; // termina il programma
}
