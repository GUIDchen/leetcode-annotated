// 题目：1094. 拼车（Car Pooling）
// 思路：差分数组。对每条行程在起点加上人数、在终点减去人数，再对差分数组求前缀和得到每个站点的实时乘车人数，一旦超过 capacity 就返回 false。
// 时间复杂度：O(n + M)，n 为行程数、M = 1000 为站点数；空间复杂度：O(M)，差分数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool carPooling(vector<vector<int>>& trips, int capacity) {  // trips 每项是 [人数, 上车点, 下车点]，capacity 为车的容量
        int d[1001]{};  // 差分数组：d[i] 是在站点 i 的净乘车人数变化量，{} 全部初始化为 0
        for (auto& trip : trips) {  // 逐条行程处理
            int x = trip[0], f = trip[1], t = trip[2];  // x 为人数，f 为上车点，t 为下车点
            d[f] += x;  // f 站上车，净人数增加 x
            d[t] -= x;  // t 站下车，净人数减少 x
        }  // 结束行程遍历
        int s = 0;  // s 为当前站点车上的总人数（差分数组的前缀和）
        for (int x : d) {  // 按站点顺序遍历差分数组
            s += x;  // 累加差分，得到该站点的实时人数
            if (s > capacity) {  // 该时刻人数超过容量
                return false;  // 说明方案不可行
            }  // 结束超载判断
        }  // 结束站点遍历
        return true;  // 全程都没有超载
    }  // 结束方法体
};  // 类定义结束