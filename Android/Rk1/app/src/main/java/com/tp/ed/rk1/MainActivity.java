package com.tp.ed.rk1;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.circle).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                openCircle();
            }
        });
        findViewById(R.id.rectangle).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                openRectangle();
            }
        });
        findViewById(R.id.cube).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                openCube();
            }
        });
    }

    private void openCircle() {
        final Intent intent = new Intent(MainActivity.this, CalcActivity.class);
        intent.setAction(CalcActivity.ACTION_CIRCLE);
        startActivity(intent);
    }

    private void openRectangle() {
        final Intent intent = new Intent(MainActivity.this, CalcActivity.class);
        intent.setAction(CalcActivity.ACTION_RECTANGLE);
        startActivity(intent);
    }

    private void openCube() {
        final Intent intent = new Intent(MainActivity.this, CalcActivity.class);
        intent.setAction(CalcActivity.ACTION_CUBE);
        startActivity(intent);
    }
}
