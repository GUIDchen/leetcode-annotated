// 题目：406. 根据身高重建队列（Queue Reconstruction by Height）
// 思路：按身高 h 降序、k 升序排序，再逐个把 [h, k] 插入到下标 k；插入时它前面的都是不低于它的已就位者。
// 时间复杂度：O(n^2)，排序 O(n log n) 加 n 次 vector 中间插入；空间复杂度：O(n)，答案数组存 n 个人。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {  // people 每项是 [h, k]：身高 h 与前面身高不低于 h 的人数 k
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {  // 自定义比较器：先按 h 降序，h 相同再按 k 升序
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);  // a 排在 b 前面当且仅当 a 更高，或等高但 k 更小
        });  // 排序后高个子全在前，后续插入时前面的人都已就位
        vector<vector<int>> ans;  // 结果队列，下标本身就代表 k（它前面的人数）
        for (const vector<int>& p : people)  // 按身高从高到低依次处理每个人
            ans.insert(ans.begin() + p[1], p);  // 高个子已排好，直接插到下标 k 处，正好有 k 个人在它前面
        return ans;  // 返回重建完成的队列
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，此处保持一致）