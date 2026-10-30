// 题目：1603. 设计停车系统（Design Parking System）
// 思路：用 cnt[carType] 保存每种车位剩余数量，carType 直接当下标，取车时非零则减一。
// 时间复杂度：构造与 addCar 均为 O(1)；空间复杂度：O(1)，只占 4 个 int。
class ParkingSystem {  // 设计题要实现的类
public:  // 对外提供的接口
    ParkingSystem(int big, int medium, int small) {  // 构造函数：big/medium/small 是三种车位的初始数量
        cnt = {0, big, medium, small};  // 下标 0 留作占位，1/2/3 分别存大/中/小车位剩余数，便于用 carType 直接索引
    }  // 构造函数结束

    bool addCar(int carType) {  // 停车：carType 取 1/2/3
        if (cnt[carType] == 0) {  // 该类型车位已停满
            return false;  // 停车失败
        }  // if 分支结束
        --cnt[carType];  // 占用一个车位，剩余数量减一
        return true;  // 停车成功
    }

private:  // 私有成员：记录各种车位的剩余数量
    vector<int> cnt;  // 4 个元素的计数数组
};  // 类定义结束

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */