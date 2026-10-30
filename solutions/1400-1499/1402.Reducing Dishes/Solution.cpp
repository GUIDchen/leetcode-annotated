// 题目：1402. 做菜顺序（Reducing Dishes）
// 思路：按满意度从大到小排序后贪心，维护后缀和 s；每加入一道菜，s 就是当前所有菜的贡献总和，把 s 累加进答案直到 s <= 0。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只用到常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSatisfaction(vector<int>& satisfaction) {  // satisfaction 每道菜的满意度
        sort(rbegin(satisfaction), rend(satisfaction));  // 用反向迭代器原地降序排序
        int ans = 0, s = 0;  // ans 为总满意度，s 为已选菜品的满意度前缀和
        for (int x : satisfaction) {  // 按满意度从高到低依次考虑
            s += x;  // 把当前菜并入集合，s 变为新的总和
            if (s <= 0) {  // 总和不再为正，继续加菜只会降低答案
                break;  // 贪心终止
            }  // 终止条件判断结束
            ans += s;  // 每道已选菜各被计入一次，累加 s 即新增贡献
        }  // 遍历结束
        return ans;  // 返回最大总满意度
    }  // maxSatisfaction 方法结束
};  // Solution 类结束