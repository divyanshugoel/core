// Copyright 2022 Divyanshu Goel.
#include "core/configManager/configParser/ConfigParserXML.h"

////////////////////////////////////////////////////////////////////////////////

crConfigParserXML::crConfigParserXML(const crFilePath& path)
    : BaseType(path)
{
}

////////////////////////////////////////////////////////////////////////////////

bool crConfigParserXML::readData()
{
    auto success = mDoc.LoadFile(mPath.get().c_str());
    checkAndReturnValue(success == tinyxml2::XML_SUCCESS, std::string("Unable to read config file. Please check path or contents : " + mPath.get()).c_str(), false);
    auto rootElement = mDoc.RootElement();
    mConfig = std::make_shared<crConfig>();
    readDataInternal(rootElement, mConfig, "");
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void crConfigParserXML::readDataInternal(const tinyxml2::XMLElement* element, fmsSP<crConfig>& config, std::string data)
{
    if (element)
    {
        std::string name(element->Name());
        // Scroll through the all child.
        auto sibling = element->FirstChildElement();
        while (sibling)
        {
            auto siblingChild = sibling->FirstChildElement();
            if (siblingChild)
            {
                // Child exists.
                std::string childName(sibling->Name());
                auto subConfig = std::make_shared<crConfig>(config);
                subConfig->name(childName);
                config->addSubConfig(subConfig);
                readDataInternal(sibling, subConfig, data + "\t");
            }
            else
            {
                // Child does not exists.
                std::string childName(sibling->Name());
                const auto childTextChr = sibling->GetText();
                if (childTextChr == NULL)
                    config->addElement(childName, "");
                else
                {
                    std::string str(childTextChr);
                    config->addElement(childName, str);
                }
            }
            sibling = sibling->NextSiblingElement();
        }
    }
    else
        fmsPrint("Null Element");
}

////////////////////////////////////////////////////////////////////////////////

void crConfigParserXML::printDataInternal()
{
    mConfig->print();
}

////////////////////////////////////////////////////////////////////////////////
