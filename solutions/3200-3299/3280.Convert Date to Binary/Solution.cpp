// 3280. 将日期转换为二进制表示（Convert Date to Binary）
// 核心思路：按 '-' 切出年、月、日三段，逐段转成整数再取其不含前导零的二进制串，最后用 '-' 拼回。
// 复杂度：时间 O(1)（固定三个数、最多 32 位），空间 O(1)

class Solution {  // 定义题解类
public:  // 公开接口
    string convertDateToBinary(string date) {  // 把 "yyyy-mm-dd" 形式的日期转换成二进制表示的日期字符串
        auto bin = [](string s) -> string {  // 辅助 lambda：把一段十进制数字字符串转成不含前导零的二进制串
            string t = bitset<32>(stoi(s)).to_string();  // 先转成整数，再得到 32 位定宽二进制串（高位补 0）
            return t.substr(t.find('1'));  // 从第一个 '1' 开始截取，去掉前导零
        };  // lambda 定义结束
        return bin(date.substr(0, 4)) + "-" + bin(date.substr(5, 2)) + "-" + bin(date.substr(8, 2));  // 分别处理年（4 位）、月（2 位）、日（2 位），再用 '-' 拼成结果
    }  // 方法结束
};  // 类定义结束
