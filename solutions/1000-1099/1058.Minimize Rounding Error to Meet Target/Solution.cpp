// 题目：1058. 最小化舍入误差以满足目标（Minimize Rounding Error to Meet Target）
// 思路：先把所有价格向下取整得到基准和 mi；若还差 d 个，就把小数部分最大的 d 个改成向上取整，其余保持向下取整，总误差最小。
// 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，保存所有小数部分。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string minimizeError(vector<string>& prices, int target) {  // prices 是价格字符串数组，target 是取整后的目标和
        int mi = 0;  // mi 记录所有价格向下取整后的总和
        vector<double> arr;  // 收集所有非零的小数部分
        for (auto& p : prices) {  // 逐个处理价格字符串
            double price = stod(p);  // 字符串转成浮点数
            mi += (int) price;  // 向下取整（价格非负，截断即下取整）后累加
            double d = price - (int) price;  // 取出小数部分
            if (d > 0) {  // 小数部分为 0 不会产生取整误差，直接忽略
                arr.push_back(d);  // 记录小数部分，供后续决定这一项是否进位
            }  // 判断结束
        }  // 统计完成
        if (target < mi || target > mi + arr.size()) {  // 目标小于全下取整之和，或大于全上取整之和，都无解
            return "-1";  // 按题目要求返回字符串 -1
        }  // 无解判断结束
        int d = target - mi;  // 还需把 d 个价格从向下取整改成向上取整
        sort(arr.rbegin(), arr.rend());  // 小数部分从大到小排序：进位的损失是 (1 - 小数)，大者先进位误差更小
        double ans = d;  // 每个进位贡献 (1 - 小数部分)，先记入 d 个 1
        for (int i = 0; i < d; ++i) {  // 前 d 个元素选择进位
            ans -= arr[i];  // 扣掉它们原本的小数部分
        }  // 进位部分统计结束
        for (int i = d; i < arr.size(); ++i) {  // 剩余元素保持向下取整
            ans += arr[i];  // 每保留一个小数部分就多出这么多误差
        }  // 不进位部分统计结束
        string s = to_string(ans);  // 转成字符串，便于截取三位小数
        return s.substr(0, s.find('.') + 4);  // 截到小数点后三位（含小数点，共 4 个字符）
    }  // 方法结束
};  // 类定义结束