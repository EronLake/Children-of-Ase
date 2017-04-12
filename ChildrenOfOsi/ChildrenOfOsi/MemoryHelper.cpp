#include "stdafx.h"
#include "MemoryHelper.h"
#include "Tag.h"


MemoryHelper::MemoryHelper()
{
	LOG("MemoryHelper Object Constructed");
}


MemoryHelper::~MemoryHelper()
{
	LOG("MemoryHelper Object Destroyed");
}


int MemoryHelper::store_hero(std::string key, float x, float y, bool col) {
	int name = 0;
	if (key == "Yemoja")
	{
		name = YEMOJA;
	}
	else if (key == "Oshosi")
	{
		name = OYA;
	}
	else if (key == "Yemoja")
	{
		name = OSHOSI;
	}
	else if (key == "Yemoja")
	{
		name = OGUN;
	}
	Hero* h = new(find_available_block(memManager::hero_head, key)) Hero(name,x, y, col);

	Containers::add_hero(key,h);
	return 0;
}

int MemoryHelper::store_soldier(std::string key, float x, float y, bool col) {
	Soldier* s = new(find_available_block(memManager::soldier_head, key)) Soldier(x, y, col);
	Containers::add_soldier(key, s);

	//std::////cout << "soldier created" << std::endl;
	//std::////cout << "soldier Address: " << s << std::endl;
	//std::////cout << "soldier xpos: " << s->getX() << std::endl;
	//std::////cout << "soldier ypos: " << s->getY() << std::endl;
	//std::////cout << "soldier col: " << s->getCollision() << std::endl;
	return 0;
}

int MemoryHelper::store_spl_soldier(std::string key, float x, float y, bool col) {
	SplSoldier* spl = new(find_available_block(memManager::spl_soldier_head, key)) SplSoldier(x, y, col);
	Containers::add_spl_soldier(key, spl);
	return 0;
}

int MemoryHelper::store_livingObj(std::string key, float x, float y, bool col) {
	LivingObj* lobj = new(find_available_block(memManager::livingObj_head, key)) LivingObj(x, y, col);
	Containers::add_livingObj(key, lobj);
	return 0;
}

int MemoryHelper::store_worldObj(std::string key, float x, float y, bool col) {
	WorldObj* wobj = new(find_available_block(memManager::worldObj_head, key)) WorldObj(x, y, col);
	if (wobj == NULL) return -1;
	Containers::add_worldObj(key, wobj);
	return 0;
}

int MemoryHelper::store_Attack(std::string key, float x, float y, bool col) {
	Attack* p = new(find_available_block(memManager::Attack_head, key)) Attack(x, y, col);
	Containers::add_Attack(key, p);
	return 0;
}

int MemoryHelper::new_Attack(WorldObj* s, int i) {
	if (s->getType() >= 3) {
		Soldier* obj = CheckClass::isSoldier(s);
		Attack* p = new(find_available_block(memManager::Attack_head, obj->getAtKey())) Attack(0, 0, true);
		Containers::add_Attack(obj->getAtKey(), p);
		obj->newAttack(i, p);
		if (p->getNextAttack() != nullptr) {
			new_Attack(obj, obj->getAttackIndex(p->getNextAttack()));
		}
	}
	return 0;
}

int MemoryHelper::store_npc(std::string key, float x, float y, bool col) {
	NPC* npc = new(find_available_block(memManager::npc_head, key)) NPC(x, y, col);
	Containers::add_npc(key, npc);
	return 0;
}


int MemoryHelper::store_texture(std::string key, float x, float y, bool col) {

	Texture* t = new(find_available_block(memManager::texture_head, key)) Texture();
	if (t == NULL) return -1;
	Containers::add_texture(key, t);
	return 0;
}

int MemoryHelper::store_memory(std::string key, int hero_name, int t, int frames, vector<NPC*> p, string cat, string cont, string where, int why, int when) {
	Memory* m;
	
	if (hero_name = OYA)
	{	
		Containers::oya_memory_table[key]->set_all(t, frames, p, cat, cont, where, why, when);
		return 0;
		/*
		Memory* m = new(find_available_block(memManager::oya_memory_head, key)) Memory(t, frames, p, cat, cont, where, why, when);
		if (m == NULL) return -1;
		Containers::add_memory(key, hero_name, m);
		return 0;
		*/
	}
	else if (hero_name = YEMOJA)
	{
		Containers::yemoja_memory_table[key]->set_all(t, frames, p, cat, cont, where, why, when);
		return 0;
		/*
		Memory* m = new(find_available_block(memManager::yemoja_memory_head, key)) Memory(t, frames, p, cat, cont, where, why, when);
		if (m == NULL) return -1;
		Containers::add_memory(key, hero_name, m);
		return 0;
		*/
	}
	else if (hero_name = OSHOSI)
	{
		Containers::oshosi_memory_table[key]->set_all(t, frames, p, cat, cont, where, why, when);
		return 0;
		/*
		Memory* m = new(find_available_block(memManager::oshosi_memory_head, key)) Memory(t, frames, p, cat, cont, where, why, when);
		if (m == NULL) return -1;
		Containers::add_memory(key, hero_name, m);
		return 0;
		*/
	}
	else if (hero_name = OGUN)
	{
		Containers::ogun_memory_table[key]->set_all(t, frames, p, cat, cont, where, why, when);
		return 0;
		/*
		Memory* m = new(find_available_block(memManager::ogun_memory_head, key)) Memory(t, frames, p, cat, cont, where, why, when);
		if (m == NULL) return -1;
		Containers::add_memory(key, hero_name, m);
		return 0;
		*/
	}
	else if (hero_name = SHANGO)
	{
		Containers::shango_memory_table[key]->set_all(t, frames, p, cat, cont, where, why, when);
		return 0;
		/*
		Memory* m = new(find_available_block(memManager::shango_memory_head, key)) Memory(t, frames, p, cat, cont, where, why, when);
		if (m == NULL) return -1;
		Containers::add_memory(key, hero_name, m);
		return 0;
		*/
	}
	
}

int MemoryHelper::store_action(std::string key, int utility, int why, Hero* owner, Hero* receiver, Hero* doer, std::string exe_name) {
	Action* a = new(find_available_block(memManager::action_head, key)) Action(owner, receiver, doer, utility, why, key, exe_name);
	if (a == NULL) return -1;
	
	/*
	a->setName(string n);
	a->setMultipliers(int a, int k, int h, int p, int r, int e, int g);
	a->setOwner(Hero* o);
	setHero(Hero* h);
	setUtility(int u);
	*/
	Containers::add_action(key, a);
	return 0;
}

int MemoryHelper::del_Attack(std::string key, float x, float y, bool col) {
	make_Available(memManager::Attack_head, memManager::Attack_pool, key);
	Containers::Attack_table.erase(Containers::Attack_table.find(key));
	return 0;
}

int MemoryHelper::store_tag(std::string key, float x, float y, bool col) {
	Tag* tag = new(find_available_block(memManager::tag_head, key)) Tag();
	Containers::add_tag(key, tag);
	return 0;
}

int MemoryHelper::store_conv_point(std::string key, float x, float y, bool col) {
	std::ofstream ofs;
	
	ConversationPoint* conv_point = new(find_available_block(memManager::conv_point_head, key)) ConversationPoint();
	Containers::add_conv_point(key, conv_point);
	//print addresses to file to check for proper storage
	/*
	ofs.open("dialog_template_output.txt", std::ofstream::out | std::ofstream::app);
	ofs << "store_check: " << conv_point << "key_check: "<< key << std::endl;
	ofs.close();*/
	return 0;
}

/////////////////////////////////////////
/*Stuff that was originally in Main*/
/////////////////////////////////////////


void* MemoryHelper::find_available_block(MemNode* head_ptr, std::string str) {
	if (head_ptr == NULL)
		return NULL;
	MemNode* mnode = head_ptr;
	while (mnode != NULL) {
		if (mnode->getAvailability()) {
			mnode->setAvailability(false);
			mnode->setUniqueString(str);
			return mnode->getBlockPointer();
		}
		mnode = mnode->getNext();
	}
	return NULL;
}

MemNode* MemoryHelper::make_Available(MemNode* head_ptr, MemoryPool* p, std::string key) {
	//size_t count = 0;
	MemNode* h = head_ptr;
	//if (node_number >= p->num_of_blocks)
		//return NULL;
	/*for (size_t i = 0; i <= node_number; ++i) {
		if (node_number != 0) {
			if (h->hasNext())
				h = h->getNext();
		}
	}*/
	while (h != NULL) {
		if (h->getUniqueString() == key) {
			h->setAvailability(true);
			return h;
		}
		//if(h->hasNext())
		h = h->getNext();

	}
	//h->setAvailability(true);
	return nullptr; //return nullptr if no object with the specified key is found
}

void MemoryHelper::destroy_MemNode_list(MemNode* head_ptr) {
	MemNode* tmp;
	while (head_ptr != NULL) {
		tmp = head_ptr;
		head_ptr = head_ptr->getNext();
		tmp->setBlockPointer(NULL);
		free(tmp);
	}
	LOG("Memory Nodes Destroyed");

}

/*Return Val: A pointer to the start of the malloced memory AKA the start
of the memory pool.
Argument(s): Takes an unsigned integer value that specifies the size of the
pool in bytes
Creates a memory pool, but does not call MemoryPool constructor.
Instead the pool exists as malloced memory that is
managed by next and end pointers. */

MemoryPool* MemoryHelper::create_pool(size_t sizeInBytes) {
	MemoryPool* p = (MemoryPool*)malloc(sizeInBytes + sizeof(MemoryPool));
	p->next = (char*)&p[1];
	p->end = p->next + sizeInBytes;
	p->pool_size = sizeInBytes;
	LOG("pool created");
	return p;
}

void MemoryHelper::destroy_pool(MemoryPool* p) {
	free(p);
	p->next = NULL;
	p->end = NULL;
	LOG("pool destroyed");
}


size_t MemoryHelper::get_free_pool_size(MemoryPool* p) {
	return p->end - p->next;
}


/*Return Value: Returns a pointer to the head of a MemNode linked list.
Arguments: Takes a pointer to the memory pool to initialize and the size in
bytes of each memory block/segment.
Creates a list of MemNodes that each store a pointer to the next node in the
list, a boolean specifying whether or not a block in the malloced memory
is available,and a pointer to a location in the malloced memory/a memory block.
Note. the block_size argument must be chosen based on the pool's size because
(pool size)/(block_size) = number of memory blocks. Must have whole number
for number of blocks.*/

MemNode* MemoryHelper::init_pool(MemoryPool *p, size_t bsize) {
	p->block_size = bsize;
	p->num_of_blocks = ((p->pool_size) / (p->block_size));
	if (get_free_pool_size(p) < bsize)
		return NULL;
	MemNode* tail;
	MemNode* head = new MemNode();
	void* memor = (void*)p->next;
	head->setAvailability(true);
	head->setBlockPointer(memor);
	p->next += bsize;
	tail = head;
	//create the list of MemNodes
	while (p->next != p->end) {
		MemNode* newNode = new MemNode();
		newNode->setAvailability(true);
		newNode->setNext(NULL);
		tail->setNext(newNode);
		tail = newNode;
		void* mem = (void*)p->next;
		newNode->setBlockPointer(mem);
		p->next += bsize;
	}
	LOG("pool initialized");
	return head;
}


void MemoryHelper::fill_mem_pool(MemNode* head_ptr, int hero_name) {
	int mem_counter = 0;
	if (head_ptr == NULL)
		return;
	MemNode* mnode = head_ptr;
	while (mnode != NULL) {
		Memory* m = new(mnode->getBlockPointer()) Memory();
		if (m == NULL) { LOG("did not work");  return; }
		Containers::add_memory(std::to_string(mem_counter), hero_name, m);
		mem_counter++;
		mnode = mnode->getNext();
	}
	return;
}


