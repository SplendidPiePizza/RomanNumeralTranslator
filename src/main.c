// src/main.c
#include <windows.h>
#include <stdio.h>
#include "roman.h"

#define MAX_INPUT_LENGTH 10

// Function to handle the message loop and GUI
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int main() {
    // Define window class and window procedure
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "RomanConverter";

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Class Registration Failed", "Error", MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindow(wc.lpszClassName, "Number to Roman Numeral Converter", WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, wc.hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "Window Creation Failed", "Error", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window procedure to handle GUI events
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    static HWND hwndInput, hwndButton, hwndResult;
    static char inputText[MAX_INPUT_LENGTH] = "";
    char result[64];

    switch (msg) {
        case WM_CREATE:
            // Create Input Field
            hwndInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
                                     20, 50, 150, 25, hwnd, (HMENU)1, ((LPCREATESTRUCT)lp)->hInstance, NULL);

            // Create Button
            hwndButton = CreateWindow("BUTTON", "Convert", WS_CHILD | WS_VISIBLE, 
                                      180, 50, 100, 30, hwnd, (HMENU)2, ((LPCREATESTRUCT)lp)->hInstance, NULL);

            // Create Output Text Area
            hwndResult = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE, 
                                      20, 100, 350, 25, hwnd, (HMENU)3, ((LPCREATESTRUCT)lp)->hInstance, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wp) == 2) {  // Convert Button Clicked
                // Get the input number
                GetWindowText(hwndInput, inputText, MAX_INPUT_LENGTH);
                int number = atoi(inputText);

                // Convert to Roman numeral
                if (number > 0 && number <= 3999) {
                    strcpy(result, toRoman(number));
                } else {
                    strcpy(result, "Invalid input! Enter a number between 1 and 3999.");
                }

                // Display result
                SetWindowText(hwndResult, result);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}
