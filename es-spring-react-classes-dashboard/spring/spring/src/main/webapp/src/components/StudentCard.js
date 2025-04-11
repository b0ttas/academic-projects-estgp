import {useNavigate, useParams} from "react-router-dom";
import React, {useEffect, useState} from "react";
import {styled} from "@mui/material/styles";
import Rating from "@mui/material/Rating";
import SentimentVeryDissatisfiedIcon from "@mui/icons-material/SentimentVeryDissatisfied";
import SentimentDissatisfiedIcon from "@mui/icons-material/SentimentDissatisfied";
import SentimentSatisfiedIcon from "@mui/icons-material/SentimentSatisfied";
import SentimentSatisfiedAltIcon from "@mui/icons-material/SentimentSatisfiedAltOutlined";
import SentimentVerySatisfiedIcon from "@mui/icons-material/SentimentVerySatisfied";
import PropTypes from "prop-types";

export default function StudentCard({student, onStudentDataChange}) {
    const role = JSON.parse(localStorage.getItem('currentUser')).role.name;
    const isReadOnly = role === 'ROLE_STUDENT';

    const {subject_id, class_id} = useParams();
    const navigate = useNavigate();

    const initialPerformance = student.performances?.find(performance => performance.classes_id === Number(class_id));
    const [performance, setPerformance] = useState(initialPerformance || {
        //id: null,
        user_id: student.id,
        classes_id: Number(class_id),
        interpretation: null,
        autonomy: null,
        interventions: null,
    });

    const attendance = performance && (performance.interpretation !== null || performance.autonomy !== null || performance.interventions !== null);

    useEffect(() => {
        onStudentDataChange(student.id, performance);
    }, [performance, student.id, onStudentDataChange, student]);

    const handleChange = (attributeName, newValue) => {
        setPerformance({...performance, [attributeName]: newValue});
    };
    //console.log(class_id);
    //console.log("performances: " + JSON.stringify(performance));

    const goStudent = ()  => {
        navigate(`/subjects/${subject_id}/classes/${class_id}/student/${student.id}`);
    }

    const StyledRating = styled(Rating)(({theme}) => ({
        '& .MuiRating-iconEmpty .MuiSvgIcon-root': {
            color: theme.palette.action.disabled,
        },
    }));

    const customIcons = {
        1: {
            icon: <SentimentVeryDissatisfiedIcon color="error"/>,
            label: 'Very Dissatisfied',
        },
        2: {
            icon: <SentimentDissatisfiedIcon color="error"/>,
            label: 'Dissatisfied',
        },
        3: {
            icon: <SentimentSatisfiedIcon color="warning"/>,
            label: 'Neutral',
        },
        4: {
            icon: <SentimentSatisfiedAltIcon color="success"/>,
            label: 'Satisfied',
        },
        5: {
            icon: <SentimentVerySatisfiedIcon color="success"/>,
            label: 'Very Satisfied',
        },
    };

    function IconContainer(props) {
        const {value, ...other} = props;
        return <span {...other}>{customIcons[value].icon}</span>;
    }

    IconContainer.propTypes = {
        value: PropTypes.number.isRequired,
    };


    return (
        <div key={student.firstName} className="student-card" >
            <div className="student-card-header">
                <div>
                    <h1 style={{color: "#007BFF"}} onClick={() => goStudent(student.id)}>
                        {student.firstName && student.lastName ? `${student.firstName} ${student.lastName}` : `User ID - ${student.id}`}
                    </h1>
                </div>
                <div>
                    <span> Attendance: </span>
                    <span>
                        <strong style={{color: attendance ? "green" : "red"}}>
                            {attendance ? "Yes" : "No"}
                        </strong>
                    </span>
                </div>
            </div>
            <div className="student-card-content">
                <div>
                    <p>Interpretation:</p>
                    <StyledRating
                        name="interpretation"
                        defaultValue={performance.interpretation}
                        IconContainerComponent={IconContainer}
                        getLabelText={(value) => customIcons[value].label}
                        highlightSelectedOnly
                        onChange={(event, newValue) => handleChange('interpretation', newValue)}
                        readOnly={isReadOnly}
                    />
                </div>
                <div>
                    <p>Autonomy:</p>
                    <StyledRating
                        name="autonomy"
                        defaultValue={performance.autonomy}
                        IconContainerComponent={IconContainer}
                        getLabelText={(value) => customIcons[value].label}
                        highlightSelectedOnly
                        onChange={(event, newValue) => handleChange('autonomy', newValue)}
                        readOnly={isReadOnly}
                    />
                </div>
                <div>
                    <p>Interventions:</p>
                    <StyledRating
                        name="interventions"
                        defaultValue={performance.interventions}
                        IconContainerComponent={IconContainer}
                        getLabelText={(value) => customIcons[value].label}
                        highlightSelectedOnly
                        onChange={(event, newValue) => handleChange('interventions', newValue)}
                        readOnly={isReadOnly}
                    />
                </div>
            </div>
        </div>
    );
}
