// 题目：2300. 咒语和药水的成功对数（Successful Pairs of Spells and Potions）
// 思路：先把药水强度升序排序，对每个咒语二分出第一个满足 spell * potion >= success 的位置，它右侧的元素个数就是成功配对数。
// 时间复杂度：O((n + m) log m)，排序加每个咒语一次二分；空间复杂度：O(n) 存放答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {  // spells：咒语强度；potions：药水强度；success：成功阈值
        ranges::sort(potions);  // 升序排序，具备单调性之后才能二分
        const int m = potions.size();  // 药水总数，后面用 m 减去下标得到成功配对数
        vector<int> ans;  // 存放每个咒语对应的成功配对数
        ans.reserve(spells.size());  // 预留容量，避免反复扩容

        for (int v : spells) {  // 逐个咒语计算结果
            auto it = ranges::lower_bound(potions, static_cast<double>(success) / v);  // 二分第一个 potions[j] >= success / v 的位置，用 double 转换避免整数除法丢精度
            ans.push_back(m - static_cast<int>(it - potions.begin()));  // 从该位置到末尾的药水都能配对成功，个数即 m 减去起始下标
        }  // 遍历结束
        return ans;  // 返回每个咒语的答案
    }  // 方法结束
};  // 类定义结束
