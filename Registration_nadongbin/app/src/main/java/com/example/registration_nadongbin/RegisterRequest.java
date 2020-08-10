package com.example.registration_nadongbin;

import com.android.volley.Response;
import com.android.volley.toolbox.StringRequest;

import java.util.HashMap;
import java.util.Map;

public class RegisterRequest extends StringRequest {

    final static private String URL = "http://localhost/phpmyadmin/db_structure.php?server=1&db=registration";
    private Map<String, String> parameters;

   public RegisterRequest(String userID, String userPassword, String userGender, String userMajor, String userEmail, Response.Listener<String> listener){
       super(Method.POST, URL, listener, null);
       parameters = new HashMap<>();
       parameters.put("userID", userID);
       parameters.put("userPassword", userPassword);
       parameters.put("userGender", userGender);
       parameters.put("userMajor", userMajor);
       parameters.put("userEmail", userEmail);
   }

   @Override
    public Map<String, String> getParams(){
       return parameters;
   }
}
