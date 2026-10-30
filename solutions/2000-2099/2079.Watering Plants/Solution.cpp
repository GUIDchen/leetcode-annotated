// 题目：2079. 给植物浇水（Watering Plants）
// 思路：顺序模拟浇水；水够则走 1 步，不够则先回河边再折返到当前位置，即多走 2*i 步，最后再前进 1 步。
// 时间复杂度：O(n)，只遍历一次 plants；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int wateringPlants(vector<int>& plants, int capacity) {  // plants：每株植物的需水量；capacity：水壶容量
        int ans = 0, water = capacity;  // ans 累计步数；water 是当前壶中剩余水量
        for (int i = 0; i < plants.size(); ++i) {  // 按顺序给每一株植物浇水
            if (water >= plants[i]) {  // 余水够浇这一株，直接走过去
                water -= plants[i];  // 消耗对应水量
                ans += 1;  // 向前走一步
            } else {  // 余水不够，必须先回河边打满水
                water = capacity - plants[i];  // 打满后立即浇掉 plants[i]
                ans += i * 2 + 1;  // 回河边再折返共 2*i 步，加上本次前进的 1 步
            }  // 结束 if-else 分支
        }  // 遍历结束
        return ans;  // 返回总步数
    }  // 关闭 wateringPlants 方法
};  // 关闭 Solution 类