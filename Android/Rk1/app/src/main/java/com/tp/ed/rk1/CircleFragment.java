package com.tp.ed.rk1;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class CircleFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View root = inflater.inflate(R.layout.fragment_circle, container, false);

        root.findViewById(R.id.solver_circle).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                try {
                    double r = Double.parseDouble(((EditText) root.findViewById(R.id.radius_circle)).getText().toString());
                    ((TextView) root.findViewById(R.id.result_circle)).setText(String.valueOf(solve(r)));
                } catch (NumberFormatException e) {
                    ((TextView) root.findViewById(R.id.result_circle)).setText(R.string.error);
                }

            }
        });
        return root;
    }

    private double solve(double r) {
        return 2 * Math.PI * r;
    }
}
