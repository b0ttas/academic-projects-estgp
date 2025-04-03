import {
    CategoryScale,
    Chart as ChartJS,
    Legend,
    LinearScale,
    LineElement,
    PointElement,
    Title,
    Tooltip,
} from 'chart.js';
import {Line} from 'react-chartjs-2';

ChartJS.register(
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
);

export default function Chart(props) {
    const options = {
        scales: {
            y: {
                min: 0,
                max: 5,
                ticks: {
                    stepSize: 1,
                },
            }
        },
        responsive: true,
        plugins: {
            legend: {
                position: 'top',
            },
            title: {
                display: true,
                text: 'Student Map',
            },
        },
    };

    const labels = props.dates.map(item => item.date);

    const avgPerformance = (props.data.avgAutonomy + props.data.avgInterpretation + props.data.avgInterventions) / 3;
    const avgAttendance = ((props.data.totalPerformances - props.data.emptyCount) / props.data.totalPerformances);

    const max = 5, min = 1;
    const data = {
        labels,
        datasets: [
            {
                label: 'Avg. Performance',
                data: labels.map(() => avgPerformance.toPrecision(3)),
                borderColor: 'rgb(255, 99, 132)',
                borderDash: [10, 10],
                backgroundColor: 'rgba(255, 99, 132, 0.5)',
            },
            {
                label: 'Interpretation',
                data: props.data.sortedPerformances.map(item => item.interpretation),
                borderColor: 'rgb(99,255,195)',
                borderWidth: 2,
                backgroundColor: 'rgba(99,255,195, 0.5)',
            },
            {
                label: 'Autonomy',
                data: props.data.sortedPerformances.map(item => item.autonomy),
                borderColor: 'rgb(203,99,255)',
                borderWidth: 6,
                backgroundColor: 'rgba(203,99,255, 0.8)',
            },
            {
                label: 'Interventions',
                data: props.data.sortedPerformances.map(item => item.interventions),
                borderColor: 'rgb(255,193,99)',
                borderWidth: 10,
                backgroundColor: 'rgba(255,193,99, 0.8)',
            },
            {
                label: 'Attendance',
                data: props.data.sortedPerformances.map(item => item.user_id ? 1 : 0),
                borderColor: 'rgb(53, 162, 235)',
                backgroundColor: 'rgba(53, 162, 235, 0.8)',
            },
            {
                label: 'Avg. Attendance',
                data: labels.map(() => avgAttendance.toPrecision(3)),
                borderColor: 'rgb(53, 162, 235)',
                borderDash: [10, 10],
                backgroundColor: 'rgba(53, 162, 235, 0.8)',
            },
        ],
    };
    return <Line options={options} data={data}/>
}

