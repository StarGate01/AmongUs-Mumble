#include <iostream>
#include <sys/mman.h>
#include <fcntl.h> 
#include <wchar.h>
#include <thread>
#include <chrono>
#include <unistd.h>

struct LinkedMem {
     uint32_t uiVersion;
     uint32_t uiTick;
     float	fAvatarPosition[3];
     float	fAvatarFront[3];
     float	fAvatarTop[3];
     wchar_t	name[256];
     float	fCameraPosition[3];
     float	fCameraFront[3];
     float	fCameraTop[3];
     wchar_t	identity[256];
     uint32_t context_len;
     unsigned char context[256];
     wchar_t description[2048];
};
LinkedMem *lm = NULL;

int main()
{
    printf("AmongUs-Mumble fake zero client for POSIX by StarGate01 (chrz.de)\n");
    printf("Press ctrl-c / cmd-c to exit\n");

    // Open shared memory file IPC
    char memname[256];
    snprintf(memname, 256, "/MumbleLink.%d", getuid());
 
    int shmfd = shm_open(memname, O_RDWR, S_IRUSR | S_IWUSR);
    if (shmfd < 0) 
    {
        printf("Cannot open shared memory: %d", shmfd);
         return 1;
    }
    lm = (LinkedMem *)(mmap(NULL, sizeof(struct LinkedMem), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd,0));
    if (lm == (void *)(-1)) 
    {
         lm = NULL;
        printf("Cannot map shared memory!");
         return 1;
    }

    while(true)
    {
        // Write state to IPC
        if (lm->uiVersion != 2)
        {
            wcsncpy(lm->name, L"Among Us", 256);
            wcsncpy(lm->description, L"Among Us support via the Link plugin.", 2048);
            lm->uiVersion = 2;
        }
        lm->uiTick++;
        // Write identity and context
        wcsncpy(lm->identity, L"Default", 256);
        memcpy(lm->context, L"TEAM", 4);
        lm->context_len = 4;
        // Write position
        for (int i = 0; i < 3; i++) 
        {
            lm->fAvatarFront[i] = 0.0f;
            lm->fAvatarTop[i] = 0.0f;
            lm->fAvatarPosition[i] = 0.0f;
            lm->fCameraFront[i] = 0.0f;
            lm->fCameraTop[i] = 0.0f;
            lm->fCameraPosition[i] = 0.0f;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}