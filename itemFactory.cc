#include "itemFactory.h"
#include "rhPotion.h"
#include "baPotion.h"
#include "bdPotion.h"
#include "phPotion.h"
#include "waPotion.h"
#include "wdPotion.h"
#include "normalGold.h"
#include "smallHoardGold.h"
#include "merchantHoardGold.h"
#include "dragonHoardGold.h"
#include "barrierSuit.h"
#include "compass.h"
#include <stdexcept>
#include <memory>

std::shared_ptr<Item> ItemFactory::createItem(std::string name) {
    if (name == "RH") return std::make_shared<RHPotion>();
    else if (name == "BA") return std::make_shared<BAPotion>();
    else if (name == "BD") return std::make_shared<BDPotion>();
    else if (name == "PH") return std::make_shared<PHPotion>();
    else if (name == "WA") return std::make_shared<WAPotion>();
    else if (name == "WD") return std::make_shared<WDPotion>();
    else if (name == "NG") return std::make_shared<NormalGold>();
    else if (name == "SH") return std::make_shared<SmallHoardGold>();
    else if (name == "MH") return std::make_shared<MerchantHoardGold>();
    else if (name == "DH") return std::make_shared<DragonHoardGold>();
    else if (name == "C") return std::make_shared<Compass>();
    else if (name == "BS") return std::make_shared<BarrierSuit>();
    else throw std::invalid_argument("Unknown item type");
}
