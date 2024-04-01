// play mode
#include "object_header.h"
#include "mode_header.h"

void play_mode() {
	// play_mode에 해당하는 객체 추가

	// 몬스터 스포너
	fw_add(new Spawner(layer_ground), layer_ground);  // 몬스터 스포너는 가장 아래쪽 레이어에서 구동

	// 맵 레이어
	fw_add(new Ground(layer_ground), layer_ground);
	fw_add(new CenterGround(layer_ground), layer_ground);

	// 맵 오브젝트 레이어
	fw_add(new Center(layer_map_object), layer_map_object);

	// 플레이어 레이어
	fw_add(new Player(layer_player), layer_player);  // 클라이언트 플레이어는 반드시 laper_player 레이어의 0번째에 위치시킬것
	
	// ui 레이어
	fw_add(new Compass(layer_ui), layer_ui);
	fw_add(new Health(layer_ui), layer_ui);
	fw_add(new Date(layer_ui), layer_ui);
	fw_add(new Text(layer_ui), layer_ui);
}