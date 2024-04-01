// play mode
#include "object_header.h"
#include "mode_header.h"

void play_mode() {
	// play_mode�� �ش��ϴ� ��ü �߰�

	// ���� ������
	fw_add(new Spawner(layer_ground), layer_ground);  // ���� �����ʴ� ���� �Ʒ��� ���̾�� ����

	// �� ���̾�
	fw_add(new Ground(layer_ground), layer_ground);
	fw_add(new CenterGround(layer_ground), layer_ground);

	// �� ������Ʈ ���̾�
	fw_add(new Center(layer_map_object), layer_map_object);

	// �÷��̾� ���̾�
	fw_add(new Player(layer_player), layer_player);  // Ŭ���̾�Ʈ �÷��̾�� �ݵ�� laper_player ���̾��� 0��°�� ��ġ��ų��
	
	// ui ���̾�
	fw_add(new Compass(layer_ui), layer_ui);
	fw_add(new Health(layer_ui), layer_ui);
	fw_add(new Date(layer_ui), layer_ui);
	fw_add(new Text(layer_ui), layer_ui);
}