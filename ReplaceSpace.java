package com.company;

import java.io.*;


public class Solution {
    private String replaceSpace (StringBuffer str) {
        String str1 = str.toString();
        char[] charArray = str1.toCharArray();
        StringBuilder sBuilder = new StringBuilder();
        for (char c : charArray) {
            if (c == ' ') {
                sBuilder.append( "#" );
            } else {
                sBuilder.append( c );
            }
        }
        return sBuilder.toString();
    }

    public static void main (String[] args) {
        File file = new File( "/Users/sephiroth/Desktop/test.txt" );
        String result = "";
        try {
            BufferedReader br = new BufferedReader( new FileReader( file ) );       //构造一个BufferedReader类来读取文件
            String s = null;
            while ((s = br.readLine()) != null) {                                   //使用readLine方法，一次读一行
                String s1 = result += s;
            }
            br.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        StringBuffer txtFile = new StringBuffer( result );
        String get = new Solution().replaceSpace( txtFile );
        System.out.print( get );
    }
}
