// 题目：2678. 老人的数目（Number of Senior Citizens）
// 思路：每位乘客的年龄固定在下标 11、12 这两个字符，切片转成整数后统计严格大于 60 的人数。
// 时间复杂度：O(n)，每个乘客只扫描一次；空间复杂度：O(1)，只用一个计数变量。
class Solution {  // 统计年龄大于 60 的乘客人数
public:  // 对外接口
    int countSeniors(vector<string>& details) {  // details 的每个元素是一条乘客信息：电话 + 性别 + 年龄 + 座位
        int ans = 0;  // ans 记录老人的人数
        for (auto& x : details) {  // 逐个乘客处理
            int age = stoi(x.substr(11, 2));  // 从下标 11 取两位就是年龄，再转成整数
            ans += age > 60;  // 布尔值会隐式转成 1/0，正好完成计数（题目要求严格大于 60）
        }  // for 结束
        return ans;  // 返回老人总数
    }  // countSeniors 结束
};  // 类定义结束