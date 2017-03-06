#include "AIController.h"

AIController::AIController()
{
	LOG("AIController object constructed");
}

AIController::~AIController()
{
	LOG("AIController object destructed");
}

void AIController::generate_end_state(int me, int them) {
	switch (me) {
	case YEMOJA:
		yemoja->choose_end_with(them);
		break;
	case OYA:
		oya->choose_end_with(them);
		break;
	case OSHOSI:
		oshosi->choose_end_with(them);
		break;
	case OGUN:
		ogun->choose_end_with(them);
		break;
	}
}