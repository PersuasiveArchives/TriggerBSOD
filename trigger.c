#include <windows.h>
#include <stdio.h>

void trigger_kmode_exception() {
    // Trigger a KMODE_EXCEPTION_NOT_HANDLED (0x1E) BSOD
    int* ptr = NULL;
    *ptr = 0;  
}

void trigger_page_fault() {
    // Trigger a PAGE_FAULT_IN_NONPAGED_AREA (0x50) BSOD
    int* ptr = (int*)0x1000;  
    *ptr = 42;
}

void trigger_system_service_exception() {
    // Trigger a SYSTEM_SERVICE_EXCEPTION (0x3B) BSOD
    int result = 1 / 0;  
}

void trigger_inaccessible_boot_device() {
    // Trigger INACCESSIBLE_BOOT_DEVICE (0x7B) BSOD
    HANDLE hFile = CreateFile("C:\\non_existent_file.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        
        DWORD error = GetLastError();  // This will cause an access violation
    }
}

void trigger_driver_irql_not_less_or_equal() {
    // Trigger DRIVER_IRQL_NOT_LESS_OR_EQUAL (0xD1) BSOD
    int* ptr = (int*)0x2000;  // Invalid address
    *ptr = 0;  
}

void trigger_critical_process_died() {
    // Trigger CRITICAL_PROCESS_DIED (0xEF) BSOD
    
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, GetCurrentProcessId());
    if (hProcess != NULL) {
        TerminateProcess(hProcess, 0);  // This simulates the critical process failure
    }
}

void trigger_system_thread_exception_not_handled() {
    // Trigger SYSTEM_THREAD_EXCEPTION_NOT_HANDLED (0x7E) BSOD
    int* ptr = (int*)0x1234;  // Invalid memory location
    *ptr = 0;  
}

void trigger_ntfs_file_system() {
    // Trigger NTFS_FILE_SYSTEM (0x24) BSOD
    HANDLE hFile = CreateFile("C:\\", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        // Cause an invalid operation (simulating disk issue)
    }
}

void trigger_irql_not_less_or_equal() {
    // Trigger IRQL_NOT_LESS_OR_EQUAL (0x0A) BSOD
    int* ptr = (int*)0x5000;  
    *ptr = 1;  
}

void trigger_unexpected_kernel_mode_trap() {
    // Trigger UNEXPECTED_KERNEL_MODE_TRAP (0x7F) BSOD
    int* ptr = (int*)0x7F7F7F7F;  // Invalid address
    *ptr = 0;  
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            if (LOWORD(wp) == 1) { // KMODE_EXCEPTION_NOT_HANDLED button
                trigger_kmode_exception();
            } else if (LOWORD(wp) == 2) { // PAGE_FAULT_IN_NONPAGED_AREA button
                trigger_page_fault();
            } else if (LOWORD(wp) == 3) { // SYSTEM_SERVICE_EXCEPTION button
                trigger_system_service_exception();
            } else if (LOWORD(wp) == 4) { // INACCESSIBLE_BOOT_DEVICE button
                trigger_inaccessible_boot_device();
            } else if (LOWORD(wp) == 5) { // DRIVER_IRQL_NOT_LESS_OR_EQUAL button
                trigger_driver_irql_not_less_or_equal();
            } else if (LOWORD(wp) == 6) { // CRITICAL_PROCESS_DIED button
                trigger_critical_process_died();
            } else if (LOWORD(wp) == 7) { // SYSTEM_THREAD_EXCEPTION_NOT_HANDLED button
                trigger_system_thread_exception_not_handled();
            } else if (LOWORD(wp) == 8) { // NTFS_FILE_SYSTEM button
                trigger_ntfs_file_system();
            } else if (LOWORD(wp) == 9) { // IRQL_NOT_LESS_OR_EQUAL button
                trigger_irql_not_less_or_equal();
            } else if (LOWORD(wp) == 10) { // UNEXPECTED_KERNEL_MODE_TRAP button
                trigger_unexpected_kernel_mode_trap();
            }
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int main() {
    // Define the window class
    const char className[] = "BSODTriggerWindow";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = className;


    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window class registration failed!", "Error", MB_ICONERROR);
        return 1;
    }


    HWND hwnd = CreateWindow(className, "BSOD Trigger", WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, 300, 400, NULL, NULL, wc.hInstance, NULL);
    if (!hwnd) {
        MessageBox(NULL, "Window creation failed!", "Error", MB_ICONERROR);
        return 1;
    }


    CreateWindow("BUTTON", "KMODE_EXCEPTION_NOT_HANDLED (0x1E)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 20, 240, 40, hwnd, (HMENU)1, wc.hInstance, NULL);

    CreateWindow("BUTTON", "PAGE_FAULT_IN_NONPAGED_AREA (0x50)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 70, 240, 40, hwnd, (HMENU)2, wc.hInstance, NULL);

    CreateWindow("BUTTON", "SYSTEM_SERVICE_EXCEPTION (0x3B)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 120, 240, 40, hwnd, (HMENU)3, wc.hInstance, NULL);

    CreateWindow("BUTTON", "INACCESSIBLE_BOOT_DEVICE (0x7B)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 170, 240, 40, hwnd, (HMENU)4, wc.hInstance, NULL);

    CreateWindow("BUTTON", "DRIVER_IRQL_NOT_LESS_OR_EQUAL (0xD1)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 220, 240, 40, hwnd, (HMENU)5, wc.hInstance, NULL);

    CreateWindow("BUTTON", "CRITICAL_PROCESS_DIED (0xEF)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 270, 240, 40, hwnd, (HMENU)6, wc.hInstance, NULL);

    CreateWindow("BUTTON", "SYSTEM_THREAD_EXCEPTION_NOT_HANDLED (0x7E)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 320, 240, 40, hwnd, (HMENU)7, wc.hInstance, NULL);

    CreateWindow("BUTTON", "NTFS_FILE_SYSTEM (0x24)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 370, 240, 40, hwnd, (HMENU)8, wc.hInstance, NULL);

    CreateWindow("BUTTON", "IRQL_NOT_LESS_OR_EQUAL (0x0A)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 420, 240, 40, hwnd, (HMENU)9, wc.hInstance, NULL);

    CreateWindow("BUTTON", "UNEXPECTED_KERNEL_MODE_TRAP (0x7F)", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 30, 470, 240, 40, hwnd, (HMENU)10, wc.hInstance, NULL);


    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Message loop to keep the window responsive
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
