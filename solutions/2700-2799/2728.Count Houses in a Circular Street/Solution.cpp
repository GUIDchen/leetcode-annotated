// 题目：2728. 计算一个环形街道上的房屋数量（Count Houses in a Circular Street）
// 思路：题目保证 0 号房为空，先把左侧 k 个房间的门全部打开作为标记，再一路向左走，遇到未打开的门即走完一圈。
// 时间复杂度：O(k + n)，n 为房屋数量；空间复杂度：O(1)。
/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void openDoor();
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 *     void moveLeft();
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int houseCount(Street* street, int k) {  // k 为街道上的房屋数量上限，返回环形街道上的房屋总数
        while (k--) {  // 先把左侧 k 个房间的门都打开，形成一段连续的标记区间
            street->openDoor();  // 打开当前房间的门（本来没开才有效果）
            street->moveLeft();  // 向左移动一格
        }
        int ans = 0;  // 计数器：统计到的房屋数量
        while (street->isDoorOpen()) {  // 一直向左走，直到遇到一扇没开的门，说明已经绕了一圈
            ans++;  // 当前房间是房屋，数量加一
            street->closeDoor();  // 关掉这扇门，防止绕回来时重复计数
            street->moveLeft();  // 继续向左移动
        }
        return ans;  // 返回环形街道上的房屋总数
    }
};