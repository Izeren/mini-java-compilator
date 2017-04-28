#include "TempLivnessFiller.h"



int processCodeLine(AssemblyCode::CodeLine* codeLine) {
    int changesCount = 0;

    for (auto useTemp : codeLine->command->GetIn()) {
        if (codeLine->liveInTemps.find(useTemp.ToString()) == codeLine->liveInTemps.end()) {
            changesCount += 1;
            codeLine->liveInTemps.insert(useTemp.ToString());
        }
    }

    for (auto liveInTemp : codeLine->liveInTemps) {
        for (auto prevLine : codeLine->prevLines) {
            if (prevLine->liveOutTemps.find(liveInTemp) == prevLine->liveOutTemps.end()) {
                changesCount += 1;
                prevLine->liveOutTemps.insert(liveInTemp);
            }
        }
    }

    for (auto liveOutTemp : codeLine->liveOutTemps) {
        bool found = false;
        for (auto outTemp : codeLine->command->GetOut()) {
            if (outTemp.ToString() == liveOutTemp) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (codeLine->liveInTemps.find(liveOutTemp) == codeLine->liveInTemps.end()) {
                changesCount += 1;
                codeLine->liveInTemps.insert(liveOutTemp);
            }
        }
    }

    return changesCount;
}

bool doIteration(std::vector<AssemblyCode::CodeLine> &lines) {
    int changesCount = 0;

    for (size_t i = (lines.size() - 1); i >= 0; --i) {
        changesCount += processCodeLine(&lines[i]);
    }

    return changesCount == 0;
}

void ::AssemblyCode::fillCodeLineTempLivness(std::vector<AssemblyCode::CodeLine> &lines) {
    while (!doIteration(lines)) {
        // 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾 👻 💀 ☠️ 👽 👾
    }
}
