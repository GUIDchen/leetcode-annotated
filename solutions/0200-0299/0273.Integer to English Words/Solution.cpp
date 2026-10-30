// 题目：273. 整数转换英文表示（Integer to English Words）
// 思路：从高位到低位每 3 位一组，用 transfer 递归拼出组内英文，再按组拼上 Billion/Million/Thousand 单位。
// 时间复杂度：O(1)，整数最多 10 位、分 4 组；空间复杂度：O(1)，只用到几张常量表与结果串。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口；下面的单词表作为 public 成员方便直接用
    vector<string> lt20 = {  // 0~19 的英文单词表，下标就是数字本身
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
        "Sixteen", "Seventeen", "Eighteen", "Nineteen"};  // 表结束：19 个单词

    vector<string> tens = {  // 十位单词表，下标是十位上的数字
        "", "Ten", "Twenty", "Thirty", "Forty", "Fifty",
        "Sixty", "Seventy", "Eighty", "Ninety"};  // 十位表结束

    vector<string> thousands = {"Billion", "Million", "Thousand", ""};  // 每 3 位一组的单位名，依次对应 10^9、10^6、10^3、个位

    string numberToWords(int num) {  // num：待转换的非负整数
        if (num == 0) {  // 0 是需要特判的唯一情况
            return "Zero";  // 直接返回单词 Zero
        }
        string res;  // 拼接最终结果
        for (int i = 1000000000, j = 0; i > 0; i /= 1000, ++j) {  // i：当前组权值，从 10^9 起每轮除以 1000；j：当前组对应的单位下标
            int cur = num / i;  // 取出当前 3 位一组的数值
            if (cur == 0) {  // 这一组为 0 就整组跳过
                continue;  // 进入下一组，避免留下多余空格
            }
            if (!res.empty()) {  // 不是第一段时补空格分隔
                res += ' ';  // 补一个空格
            }
            res += transfer(cur);  // 把这一组 3 位数递归转成英文
            if (!thousands[j].empty()) {  // 不是个位组才有单位名要拼
                res += ' ';  // 单位前补空格
                res += thousands[j];  // 拼上单位名称
            }
            num %= i;  // 去掉已经处理过的高位
        }
        return res;  // 返回完整英文表示
    }

private:  // 内部辅助函数放在 private 中
    string transfer(int num) {  // 把 0~999 的数转成英文（不含前后空格）
        if (num == 0) {  // 0 返回空串，避免多出单词
            return "";  // 返回空串
        }
        if (num < 20) {  // 20 以内直接查表
            return lt20[num];  // 查表返回单词
        }
        if (num < 100) {  // 100 以内用十位表
            if (num % 10 == 0) {  // 整十数直接查十位表
                return tens[num / 10];  // 返回十位单词
            }
            return tens[num / 10] + " " + transfer(num % 10);  // 否则拼成「十位单词 + 个位递归」
        }
        if (num % 100 == 0) {  // 整百数：如 One Hundred
            return lt20[num / 100] + " Hundred";  // 百位单词 + Hundred
        }
        return lt20[num / 100] + " Hundred " + transfer(num % 100);  // 其余：百位 + Hundred + 余下两位的递归结果
    }
};
