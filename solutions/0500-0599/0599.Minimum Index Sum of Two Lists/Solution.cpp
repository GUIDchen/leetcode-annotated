// 题目：599. 两个列表的最小索引总和（Minimum Index Sum of Two Lists）
// 思路：先把 list2 建成「餐厅名 → 下标」的哈希表，再遍历 list1 边查表边维护最小索引和及其对应的所有餐厅。
// 时间复杂度：O(m + n)，两次线性遍历；空间复杂度：O(n)，哈希表保存 list2 的全部餐厅。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {  // list1、list2 是两个人的餐厅偏好列表，要求返回索引和最小的共同餐厅
        unordered_map<string, int> d;  // 哈希表：键是 list2 中的餐厅名，值是它在 list2 中的下标
        for (int i = 0; i < list2.size(); ++i) {  // 先完整扫描 list2，建立名字到下标的一一映射
            d[list2[i]] = i;  // 记录下当前餐厅在 list2 中的位置，供后面 O(1) 查表
        }  // list2 的映射建立完毕
        vector<string> ans;  // 结果集：保存当前最小索引和对应的所有餐厅（可能有多个并列）
        int mi = INT_MAX;  // 最小索引和，初始化为无穷大保证第一个匹配一定能更新
        for (int i = 0; i < list1.size(); ++i) {  // 遍历 list1，此时 i 就是该餐厅在 list1 中的下标
            if (d.contains(list1[i])) {  // 只有同时出现在 list2 中的餐厅才可能计入答案
                int j = d[list1[i]];  // 取出同一个餐厅在 list2 中的下标 j
                if (i + j < mi) {  // 发现更小的索引和：之前的候选全部作废，以当前餐厅为准
                    mi = i + j;  // 更新当前的最小索引和
                    ans.clear();  // 清空旧的并列候选，因为已经不是最小索引和了
                    ans.push_back(list1[i]);  // 把当前餐厅作为新的唯一候选放入结果
                } else if (i + j == mi) {  // 索引和与当前最小值相等：该餐厅与已有候选并列
                    ans.push_back(list1[i]);  // 并列时追加进结果集，全部保留
                }  // 索引和判断分支结束
            }  // 配对判断结束
        }  // list1 遍历结束
        return ans;  // 返回所有索引和最小的共同餐厅
    }  // 方法结束
};  // 类定义结束
