// 题目：1243. 数组变换（Array Transformation）
// 思路：按天迭代，每轮先用快照判断所有内部元素的峰谷并同时增减，直到某一轮不再发生任何变化。
// 时间复杂度：O(d·n)，d 为收敛轮数（元素值有界所以 d 有限）；空间复杂度：O(n)，用于保存当轮快照。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    vector<int> transformArray(vector<int>& arr) {  // 原地变换数组，返回变化停止后的数组
        bool f = true;  // 标记「本轮是否发生过变化」，初值为 true 以进入循环
        while (f) {  // 只要上一轮还有元素变化就继续迭代
            f = false;  // 先假设本轮不会再变化
            vector<int> t = arr;  // 复制快照，本轮判断全部基于上一轮的状态，避免先后影响
            for (int i = 1; i < arr.size() - 1; ++i) {  // 首尾元素不会变化，只考察内部元素
                if (t[i] > t[i - 1] && t[i] > t[i + 1]) {  // 严格大于左右邻居，说明是局部峰
                    --arr[i];  // 峰顶减一
                    f = true;  // 记录本轮发生了修改
                }
                if (t[i] < t[i - 1] && t[i] < t[i + 1]) {  // 严格小于左右邻居，说明是局部谷
                    ++arr[i];  // 谷底加一
                    f = true;  // 记录本轮发生了修改
                }
            }
        }
        return arr;  // 不再变化时即为最终数组
    }
};  // 类定义结束