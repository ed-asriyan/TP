package com.tp.ed.rk1;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;

public class CalcActivity extends AppCompatActivity {
    public static final String ACTION_CIRCLE = "danya";
    public static final String ACTION_RECTANGLE = "andrey";
    public static final String ACTION_CUBE = "sergey";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_calc);

        switch (getIntent().getAction()) {
            case ACTION_CIRCLE:
                createCircleFragment();
                break;
            case ACTION_RECTANGLE:
                createRectangleFragment();
                break;
            case ACTION_CUBE:
                createCubeFragment();
                break;
        }
    }

    private void createCircleFragment() {
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();

        transaction.add(R.id.calc_container, new CircleFragment());

        transaction.commit();
    }

    private void createRectangleFragment() {
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();

        transaction.add(R.id.calc_container, new RectangleFragment());

        transaction.commit();
    }
    private void createCubeFragment() {
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();

        transaction.add(R.id.calc_container, new CubeFragment());

        transaction.commit();
    }
}
