#include <fstream>

#include "core/core/Core.h"

int main()
{
    Uuid value;
    Uuid value1;
    Uuid value2;
    Uuid value3;
    Uuid value4;
    Uuid value5;
    Uuid value6;

    value.autoAssign();
    value1.autoAssign("common");

    value2.autoAssign("agentSample");
    value3.autoAssign("agentSample");
    value4.autoAssign("robot");
    value5.autoAssign("robot");

    value.print();
    value1.print();
    value2.print();
    value3.print();
    value4.print();
    value5.print();
    value6.print();
    value6 = value5;
    value6.print();
    if (value6 == 2)
        fmsPrint("ID == 2");
    if (2 == value6)
        fmsPrint("2 == ID");

    if (value6 != 3)
        fmsPrint("ID != 3");
    if (3 != value6)
        fmsPrint("3 != ID");

    const auto& gen = value.getGenerator();
    const auto& cate = gen->getCategories();
    fmsPrintRepeated("_", 30);
    for (const auto& cat : cate)
        fmsPrint_("Category : %s", cat.c_str());
    fmsPrintRepeated("_", 30);
}
