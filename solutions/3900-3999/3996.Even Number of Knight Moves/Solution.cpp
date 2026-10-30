// 3996. 偶数次骑士移动 / Even Number of Knight Moves（简单）
// 核心思路：骑士每走一步都会把所在格的行与列奇偶性同时翻转，因此「走偶数步可达」等价于起点与终点坐标和 (x + y) 的奇偶性相同。
// 复杂度：时间 O(1)，空间 O(1)。
class Solution {  // 题解类
public:  // 公有接口
    bool canReach(vector<int>& start, vector<int>& target) {  // 返回骑士能否用偶数次移动从 start 到达 target
        return (start[0] + start[1]) % 2 == (target[0] + target[1]) % 2;  // 两格坐标和的奇偶性相同即可用偶数步互相到达
    }  // 方法结束
};  // 类定义结束