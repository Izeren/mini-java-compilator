#include "../utils/Frame.h"

bool isInIgnoreList(std::string& temp) {
    if (temp == IRT::CFrame::returnValueAddressName) {
        return true;
    }

    if (temp == IRT::CFrame::framePointerAddressName) {
        return true;
    }

    return false;
}
