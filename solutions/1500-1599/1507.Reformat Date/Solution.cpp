// 题目：1507. 转变日期格式（Reformat Date）
// 思路：用 stringstream 依次拆出日、月、年，再用月份表定位月份序号，最后各自补零拼成 YYYY-MM-DD。
// 时间复杂度：O(L)，L 为日期串长度（常数级）；空间复杂度：O(L)，保存月份表与拆出的字段。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    string reformatDate(string date) {  // date 形如 "20th Oct 2052"，返回 "2052-10-20"
        string months = " JanFebMarAprMayJunJulAugSepOctNovDec";  // 从下标 1 起每 3 个字符对应一个月份，便于用 find 反查月份序号
        stringstream ss(date);  // 用字符串流把日期按空白切成若干字段
        string year, month, t;  // year 年份、month 英文月份、t 带序数后缀的日
        int day;  // day 日（整数形式）
        ss >> day >> t >> month >> year;  // 依次读入：日（读到非数字即停）、单词 t、月份、年份
        month = to_string(months.find(month) / 3 + 1);  // find 得到月份在表中的起始下标，除以 3 得 0..11，加 1 即为 1..12
        return year + "-" + (month.size() == 1 ? "0" + month : month) + "-" + (day > 9 ? "" : "0") + to_string(day);  // 月份和日不足两位时补前导零，拼成 YYYY-MM-DD
    }
};