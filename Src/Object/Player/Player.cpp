#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SystemManager.h"
#include "../../Utility/AsoUtility.h"
#include "Player.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Load(void)
{
	//// モデルのロード
	//player_.modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());
}

void Player::Init(void)
{
	// 座標の設定
	player_.pos_ = player_.prevPos_ = DEFAULT_POS;
	//MV1SetPosition(player_.modelId_, player_.pos_);

	// 向きの設定
	player_.angles_ = AsoUtility::VECTOR_ZERO;
	//MV1SetRotationXYZ(player_.modelId_, player_.angles_);

	// 大きさの設定
	player_.scales_ = SCALES;
	//MV1SetScale(player_.modelId_, player_.scales_);

	// HPの初期化
	player_.hp_ = MAX_HP;

	player_.moveSpeed_ = SPEED_MOVE;

	mouse_ = { 0,0 };

	// 他の場所で設定された感度入れる
	sensitivity_ = SystemManager::GetInstance().GetSensitivity();
}

void Player::Update(void)
{
	// 移動
	ProcessMove();

	// 視点移動
	ProcessAngle();
}

void Player::Draw(void)
{
#ifdef _DEBUG
	DrawFormatString(0, 20, 0xffffff, "プレイヤー座標：%.2f,%.2f,%.2f", player_.pos_.x, player_.pos_.y, player_.pos_.z);
#endif // _DEBUG

}

void Player::Release(void)
{
}

void Player::ProcessMove(void)
{
	InputManager& ins = InputManager::GetInstance();

	// 移動方向
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	// 奥
	if (ins.MoveFront()) { moveDir.z += 1.0f; }
	// 手前
	if (ins.MoveBack()) { moveDir.z -= 1.0f; }
	// 左
	if (ins.MoveLeft()) { moveDir.x -= 1.0f; }
	// 右
	if (ins.MoveRight()) { moveDir.x += 1.0f; }


	if (!AsoUtility::EqualsVZero(moveDir))
	{

		// ベクトルの大きさを計算
		float length = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);

		if (length == 0.0f)
		{
			moveDir.x = moveDir.z = 0.0f;
		}

		// 大きさで割って単位ベクトルにする
		moveDir.x /= length;
		moveDir.z /= length;

		player_.moveDir_ = moveDir;

		VECTOR movePow;

		if (ins.MoveDash())
		{
			player_.moveSpeed_ = SPEED_MOVE_MAX;
		}
		else
		{
			player_.moveSpeed_ = SPEED_MOVE;
		}

		// 移動量を計算する(方向＊スピード)
		movePow = VScale(moveDir, player_.moveSpeed_);

		// 移動処理(座標＋移動量)
		player_.pos_ = VAdd(player_.pos_, movePow);

		// モデルに座標を設定
		//MV1SetPosition(modelId_, pos_);

		// 方向から角度を出す
		//player_.angles_.y = atan2(moveDir.x, moveDir.z);

		// モデルに向きを設定
		//MV1SetRotationXYZ(modelId_, angles_);

	}
}

void Player::ProcessAngle(void)
{
	// カメラの回転量
	int yaw_ = 0,pitch_ = 0;

	// 現在のマウス座標を取得
	GetMousePoint(&mouse_.x, &mouse_.y);

	// 画面中央からのマウスの移動量を調べる
	int deltaX = mouse_.x - Application::SCREEN_SIZE_X / 2;
	int deltaY = mouse_.y - Application::SCREEN_SIZE_Y / 2;

	// マウスの移動量からカメラの回転量を更新する
	yaw_ += deltaX * sensitivity_;
	pitch_ += deltaY * sensitivity_;

	// ピッチ角の角度制限（真上や真下を向きすぎないようにする）
	if (pitch_ > 1.5f)
	{
		pitch_ = 1.5f;
	}
	if (pitch_ < -1.5f)
	{
		pitch_ = -1.5f;
	}

	// 回転量から実際に回転させる
	player_.angles_.x = player_.pos_.x + sinf(yaw_) * cosf(pitch_);
	player_.angles_.y = player_.pos_.y + sinf(pitch_);
	player_.angles_.x = player_.pos_.z + cosf(yaw_) * cosf(pitch_);
}
