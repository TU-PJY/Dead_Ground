// play mode
#include "object_header.h"
#include "mode_header.h"

void play_mode() {
	// play_mode�� �ش��ϴ� ��ü �߰�
	// 1�� ���̾�
	fw_add(new Ground(layer_ground), layer_ground);

	// 2�� ���̾�
	fw_add(new Player(layer_player), layer_player);
}