// play mode
#include "object_header.h"
#include "mode_header.h"

void play_mode() {
	// play_mode에 해당하는 객체 추가
	// 1번 레이어
	fw_add(new Ground(layer_ground), layer_ground);

	// 2번 레이어
	fw_add(new Player(layer_player), layer_player);
}