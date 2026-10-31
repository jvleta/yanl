// import { Chart, registerables } from 'https://jsdelivr.net';
import {
  Chart,
  registerables,
} from "https://cdn.jsdelivr.net/npm/chart.js@4.4.0/+esm";

// In v4 module builds, you need to register components/controllers
// so Chart.js knows how to render them (e.g. scales, legends, bars)
Chart.register(...registerables);

import initYanlWasm from "./yanl_wasm.js";

const ctx = document.getElementById("myChart").getContext("2d");

const func = (x) => x * x - 1.0;

const linspace = (xmin, xmax, numPoints) => {
  const x = [];
  const dx = (xmax - xmin) / (numPoints - 1).toFixed(2);
  for (let i = 0; i < numPoints; i++) {
    x.push(xmin + i * dx);
  }
  return x;
};

const makeData = () => {
  const xdata = linspace(-5.0, 5.0, 1000);
  const data = xdata.map((x) => {
    return { x, y: func(x) };
  });
  console.log(data);
  return data;
};

initYanlWasm().then((Module) => {
  Module.dostuff();
  const result = Module.bisection(func, -10, 0, 0.00001);
  new Chart(ctx, {
    type: "scatter",
    data: {
      label: "blah blah blah",
      datasets: [
        {
          label: "Monthly Sales",
          data: makeData(),
          showLine: true,
        },
        {
          label: "root",
          data: [{ x: result.root, y: 0.0 }],
          showLine: true,
        },
      ],
    },
  });
});
