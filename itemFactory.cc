#include "itemFactory.h"
#include "rhPotion.h"
#include "baPotion.h"
#include "bdPotion.h"
#include "phPotion.h"
#include "waPotion.h"
#include "wdPotion.h"
#include "smallGold.h"
#include "normalGold.h"
#include "smallHoardGold.h"
#include "merchantHoardGold.h"
#include "dragonHoardGold.h"
#include "barrierSuit.h"
#include "compass.h"
#include <stdexcept>
#include <memory>

std::unique_ptr<Item> ItemFactory::create(const std::string &type, Cell* pos, Floor* fl) {
    if (type == "RH") return std::make_unique<RHPotion>(pos, fl);
    else if (type == "BA") return std::make_unique<BAPotion>(pos, fl);
    else if (type == "BD") return std::make_unique<BDPotion>(pos, fl);
    else if (type == "PH") return std::make_unique<PHPotion>(pos, fl);
    else if (type == "WA") return std::make_unique<WAPotion>(pos, fl);
    else if (type == "WD") return std::make_unique<WDPotion>(pos, fl);
    else if (type == "SmallGold") return std::make_unique<SmallGold>(pos, fl);
    else if (type == "NormalGold") return std::make_unique<NormalGold>(pos, fl);
    else if (type == "SmallHoardGold") return std::make_unique<SmallHoardGold>(pos, fl);
    else if (type == "MerchantHoardGold") return std::make_unique<MerchantHoardGold>(pos, fl);
    else if (type == "DragonHoardGold") return std::make_unique<DragonHoardGold>(pos, fl);
    else if (type == "BarrierSuit") return std::make_unique<BarrierSuit>(pos, fl);
    else if (type == "Compass") return std::make_unique<Compass>(pos, fl);
    else throw std::invalid_argument("Unknown item type");
}
