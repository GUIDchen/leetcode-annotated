// 题目：1122. 数组的相对排序（Relative Sort Array）
// 思路：给 arr2 中的值一个按下标递增的优先级，arr1 中没出现的值统一给最大优先级；排序键 (优先级, 值) 一次排序即满足「arr2 顺序 + 其余升序」。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(n)，哈希表与辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {  // 按 arr2 中的相对顺序重排 arr1，arr2 里没有的元素升序排在后面
        unordered_map<int, int> pos;  // 值 → 它在 arr2 中的下标，这个下标就是排序优先级
        for (int i = 0; i < arr2.size(); ++i) {  // 顺序遍历 arr2，下标天然递增
            pos[arr2[i]] = i;  // 下标越小优先级越高，排序后越靠前
        }  // 建表循环结束
        vector<pair<int, int>> arr;  // 辅助数组：每个元素打包成 (优先级, 值)
        for (int i = 0; i < arr1.size(); ++i) {  // 遍历 arr1 逐个生成排序键
            int j = pos.count(arr1[i]) ? pos[arr1[i]] : arr2.size();  // 在 arr2 中出现过就用它的下标；否则统一给 arr2.size()，保证都排在后面
            arr.emplace_back(j, arr1[i]);  // 入队，值本身作为第二关键字，用于「其余元素升序」
        }  // 构造辅助数组结束
        sort(arr.begin(), arr.end());  // pair 默认按字典序比较：先比优先级，优先级相同再比值
        for (int i = 0; i < arr1.size(); ++i) {  // 把排好序的值写回原数组，保持返回类型一致
            arr1[i] = arr[i].second;  // 取出 (优先级, 值) 里的值
        }  // 写回循环结束
        return arr1;  // 返回重排后的 arr1
    }  // 方法结束
};  // 类定义结束