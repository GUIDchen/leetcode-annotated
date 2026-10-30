// 题目：1868. 两个行程编码数组的积（Product of Two Run-Length Encoded Arrays）
// 思路：双指针按行程对齐切分两个编码数组，每次取两段剩余长度的较小值作为公共长度，乘积相同则与答案末段合并。
// 时间复杂度：O(m + n)，两数组的行程段各自只被消耗一次；空间复杂度：O(m + n)，答案最多有 m + n 段。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {  // encoded1、encoded2：行程编码数组，每项为 {值, 连续段长度}
        vector<vector<int>> ans;  // 答案同样用 {值, 段长度} 存放乘积的行程编码
        int j = 0;  // j：encoded2 中当前正在消耗的行程段下标
        for (auto& e : encoded1) {  // 依次遍历 encoded1 的每个行程段
            int vi = e[0], fi = e[1];  // vi：本段的值；fi：本段尚未被消耗的长度
            while (fi) {  // 本段还有剩余长度，就继续和 encoded2 对齐切分
                int f = min(fi, encoded2[j][1]);  // 取两段剩余长度的较小值，作为这一次对齐的公共长度
                int v = vi * encoded2[j][0];  // 两段的值相乘，得到这段公共区间的乘积
                if (!ans.empty() && ans.back()[0] == v) {  // 乘积与答案末段相同就合并，保证行程编码尽量短
                    ans.back()[1] += f;  // 末段长度累加本次段长
                } else {  // 乘积不同，必须新开一段
                    ans.push_back({v, f});  // 记录新的 {乘积, 长度}
                }  // 结束 if/else 分支
                fi -= f;  // 扣掉 encoded1 本次已经消耗的长度
                encoded2[j][1] -= f;  // encoded2 当前段同步扣掉相同长度
                if (encoded2[j][1] == 0) {  // 当前段被消耗完
                    ++j;  // 指针右移，准备使用下一段
                }  // 结束 if
            }  // 结束 while
        }  // 结束 for
        return ans;  // 返回合并后的乘积行程编码
    }  // 结束方法
};  // 结束类