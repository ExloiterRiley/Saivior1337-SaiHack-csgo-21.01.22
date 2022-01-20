#include "m_headers.h"

int main()
{
    con->setupConsole();
    offsets->DownloadOffsets();
    mem->startMemory();
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)d3d->CreateDirectWindow, NULL, NULL, NULL);
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)iModels->SetKnife, NULL, NULL, NULL);
    while (true)
    {
        con->terminateThread();

        if (LocalPlayer::isInGame())
        {
            if (CFG.triggerBot)
                iAimbot->Trigger();

            for (int i = 0; i < 64; i++)
            {
                DWORD entity = Entity::getEntityBase(i);
                if (entity != NULL && Entity::isEntityValid(entity))
                {
                    if (CFG.radar)
                        iVisuals->InGameRadar(entity);

                    if (CFG.glow)
                        iVisuals->Glow(entity);

                    if (CFG.clrRender)
                        iVisuals->RenderChams(entity);

                    if (CFG.hitSound)
                        iMisc->Sound();

                    if (CFG.bunnyHop)
                        iMisc->Bunny();

                    if (CFG.AimBotB)
                        iAimbot->Aim(iAimbot->getPlayer(), entity);

                }
            }
        }
        std::this_thread::sleep_for(1ms);
    }
    return 0;
}
