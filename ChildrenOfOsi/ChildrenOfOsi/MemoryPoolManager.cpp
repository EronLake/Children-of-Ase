#include "MemoryPoolManager.h"
#include "StandardMemoryPool.h"
#include "../TinyXML/tinyxml.h"

const char* const	MemoryPoolManager::c_poolsFileXML = "./pools.xml";
	
/**
*	\brief		Construct the manager reading from the provided xml files all the pools
*/
MemoryPoolManager::MemoryPoolManager(const char* const poolsFileXML)
{
	TiXmlDocument doc( poolsFileXML );
	if(doc.LoadFile())
	{
		TiXmlNode* root = doc.FirstChild( "memorypools" );
        ASSERT(root, "File contains invalid data");
        if(root)
        {
            TiXmlNode* pool = root->FirstChildElement();
            //Create Pools
            while(pool)
            {
                if( pool->Type() == TiXmlNode::TINYXML_ELEMENT && isAValidPoolType(pool->Value()) )
                {
                    TiXmlElement* element = pool->ToElement();
                    if(element)
                    {
                        TiXmlAttribute* attribute = element->FirstAttribute();

                        char name[128] = {'\0'};
                        BYTE blockSize = 4;
                        DWORD size = 1024;
                        bool boundCheck = false;

                        while(attribute)
                        {
                            if(strcmp(attribute->Name(), "name") == 0) strcpy_s(name, 128, attribute->Value());
                            else
                            if(strcmp(attribute->Name(), "size") == 0) size = attribute->IntValue();
                            else
                            if(strcmp(attribute->Name(), "boundsCheck") == 0) boundCheck = attribute->IntValue() == 1 ? true : false;
                            attribute = attribute->Next();
                        }

                        MemoryPool* memPool = NULL;

                        if(strcmp(pool->Value(), "pool") == 0)       memPool = new StandardMemoryPool(size, boundCheck);

                        if(memPool)
                            m_pool.insert(std::pair<std::string, MemoryPool*>(name, memPool));
                    }
                }

                pool = pool->NextSibling();
            }
        }
	}
    else
    {
        ERROR("Memory pool set XML file not found");
    }
}

/**
*	\brief		Check if the pool type in string form is a valid recognized pool type.
*/
bool MemoryPoolManager::isAValidPoolType(const char* poolType) const
{
    if(strcmp(poolType, "pool") == 0) return true;
    return false;
}