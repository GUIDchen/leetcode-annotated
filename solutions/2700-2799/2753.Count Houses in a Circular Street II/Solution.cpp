// 题目：2753. 计算一个环形街道上的房屋数量 II（Count Houses in a Circular Street II）
// 思路：先向右走到任意一扇开着的门前作为起点，再沿环最多走 k 步；每遇到开着的门就关掉并记下步数，最大步数即房屋总数。
// 时间复杂度：O(n + k)，n 是走到第一扇开门房子的步数；空间复杂度：O(1)，只用了常数个变量。
// 下面是题目给出的 Street 接口定义（实现由判题器提供），本题只能通过它来探索街道。
/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int houseCount(Street* street, int k) {  // street：环形街道对象；k：允许向右移动的最大步数（不小于房屋数）
        while (!street->isDoorOpen()) {  // 先挪到一扇开着的门前，给后面的计数一个确定的起点
            street->moveRight();  // 当前门是关的，继续向右移动
        }  // 此时已停在第一扇开着的门前
        int ans = 0;  // ans 记录沿环走过的最远开门距离，也就是房屋数量
        for (int i = 1; i <= k; ++i) {  // 从起点出发最多再走 k 步，足够绕环整整一圈
            street->moveRight();  // 向右走一扇门
            if (street->isDoorOpen()) {  // 门还开着，说明这是一栋还没数过的房子
                ans = i;  // 更新最远距离，i 就是这栋房子到起点的距离
                street->closeDoor();  // 关掉门做标记，避免绕环时把同一栋房子重复统计
            }
        }
        return ans;  // 最远的开门距离就是房屋总数
    }  // 方法结束
};  // 类定义结束