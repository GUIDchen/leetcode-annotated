// 题目：2079. 给植物浇水（Watering Plants）
// 思路：从左到右顺序浇水；水够就只走 1 步，不够就先回河边（i 步）再走回当前位置（i 步）并前进 1 步，累计步数。
// 时间复杂度：O(n)，只遍历一次植物数组；空间复杂度：O(1)，只用两个整型变量记录步数与剩余水量。
int wateringPlants(int* plants, int plantsSize, int capacity) {  // plants：每株植物的需水量；plantsSize：植物数量；capacity：水壶容量
    int ans = 0, water = capacity;  // ans 累计走过的步数；water 是水壶当前剩余水量
    for (int i = 0; i < plantsSize; ++i) {  // 从左到右依次给每株植物浇水
        if (water >= plants[i]) {  // 壶里水够这株植物，直接走到它面前浇
            water -= plants[i];  // 浇掉 plants[i]，剩余水量相应减少
            ans += 1;  // 向前走一步，步数加一
        } else {  // 水不够，必须先返回河边把壶打满
            water = capacity - plants[i];  // 打满后浇掉 plants[i]，壶里剩下的是 capacity - plants[i]
            ans += i * 2 + 1;  // 从 i 回到 0 再走回 i 共 2*i 步，加上本次前进的 1 步
        }  // 结束 if-else 分支
    }  // 遍历完所有植物
    return ans;  // 返回走的总步数
}  // 函数结束