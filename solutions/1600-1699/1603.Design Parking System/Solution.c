// 题目：1603. 设计停车系统（Design Parking System）
// 思路：数组 cnt[carType] 直接记录每种车位的剩余数量，取车时判断非零再减一；构造函数完成初始化。
// 时间复杂度：构造 O(1)、停车 O(1)；空间复杂度：O(1)，只需 3 个计数器。
typedef struct {  // 停车系统结构体：设计题要求实现的类型
    int* count;  // 长度 3 的数组，下标 0/1/2 分别表示大、中、小车位的剩余数量
} ParkingSystem;  // 结构体定义结束，ParkingSystem 成为该类型的别名

ParkingSystem* parkingSystemCreate(int big, int medium, int small) {  // 构造函数：记下三种车位的初始容量
    ParkingSystem* res = malloc(sizeof(ParkingSystem));  // 为 ParkingSystem 结构体本身申请内存
    res->count = malloc(sizeof(int) * 3);  // 为计数数组申请 3 个 int 的空间
    res->count[0] = big;  // 大车位剩余数量
    res->count[1] = medium;  // 中车位剩余数量
    res->count[2] = small;  // 小车位剩余数量
    return res;  // 返回创建好的对象指针，供后续调用使用
}
  // 停车接口：carType 取 1/2/3，分别代表大/中/小车
bool parkingSystemAddCar(ParkingSystem* obj, int carType) {  // 把 1/2/3 映射成数组下标 0/1/2
    int i = carType - 1;  // 该类型车位剩余数量为 0，说明已停满
    if (!obj->count[i]) {  // 返回 0（false），表示停车失败
        return 0;  // if 分支结束
    }  // 占用一个车位：剩余数量减一
    obj->count[i]--;  // 返回 1（true），表示停车成功
    return 1;
}
  // 析构接口：释放对象占用的内存，防止内存泄漏
void parkingSystemFree(ParkingSystem* obj) {  // 释放结构体本身（内部的 count 数组随判题进程结束一并回收）
    free(obj);  // 析构函数结束
}

/**
 * Your ParkingSystem struct will be instantiated and called as such:
 * ParkingSystem* obj = parkingSystemCreate(big, medium, small);
 * bool param_1 = parkingSystemAddCar(obj, carType);

 * parkingSystemFree(obj);
*/