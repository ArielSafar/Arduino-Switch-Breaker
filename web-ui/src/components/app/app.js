import { Button, Slider, Typography } from "@material-ui/core";
import { useEffect, useState } from "react";
import InfoParam from "../info-param/info-param";
import * as motorService from "../../services/motor-service";
import ToggleButton from "@material-ui/lab/ToggleButton";
import ToggleButtonGroup from "@material-ui/lab/ToggleButtonGroup";
import RotateLeftIcon from "@material-ui/icons/RotateLeft";
import RotateRightIcon from "@material-ui/icons/RotateRight";
import "./app.scss";

function App() {
  const [motorSpeed, setMotorSpeed] = useState(null);
  const [direction, setMotorDirection] = useState(null);
  const [cwRevolutions, setCWRevolutions] = useState(null);
  const [ccwRevolutions, setCCWRevolutions] = useState(null);
  useEffect(() => {
    if (!motorSpeed) {
      motorService.getMotorSpeed().then((data) => setMotorSpeed(data.speed));
    }
  }, [motorSpeed]);

  useEffect(() => {
    if (!direction) {
      motorService
        .getDirection()
        .then((data) => setMotorDirection(data.direction));
    }
  }, [direction]);

  useEffect(() => {
    if (!cwRevolutions) {
      motorService
        .getRevolutions("CW")
        .then((data) => setCWRevolutions(data.cw_revolutions));
    }
  }, [cwRevolutions]);

  useEffect(() => {
    if (!ccwRevolutions) {
      motorService
        .getRevolutions("CCW")
        .then((data) => setCCWRevolutions(data.ccw_revolutions));
    }
  }, [ccwRevolutions]);

  return (
    <div className="app">
      <div className="title">Stepper Motor</div>
      <div className="information">
        <InfoParam title={"Speed"} value={motorSpeed && `${motorSpeed} RPM`} />
        <InfoParam title={"Direction"} value={direction} />
        <InfoParam title={"CW Revolutions"} value={cwRevolutions} />
        <InfoParam title={"CCW Revolutions"} value={ccwRevolutions} />
      </div>
      {motorSpeed && direction ? (
        <>
          <div className="inputs-container">
            <div className="speed-slider">
              <Typography id="discrete-slider" gutterBottom>
                Speed
              </Typography>
              <Slider
                defaultValue={motorSpeed}
                onChangeCommitted={async (event, value) => {
                  await motorService.setSpeed(value);
                  setMotorSpeed(value);
                }}
                getAriaValueText={(value) => `${value} RPM`}
                aria-labelledby="discrete-slider"
                valueLabelDisplay="auto"
                step={5}
                marks={[
                  {
                    value: 10,
                    label: "10 RPM",
                  },
                  {
                    value: 100,
                    label: "100RPM",
                  },
                  {
                    value: 190,
                    label: "190RPM",
                  },
                ]}
                min={10}
                max={190}
              />
            </div>

            <div className="direction-buttons">
              <Typography id="direction" gutterBottom>
                Direction
              </Typography>

              <ToggleButtonGroup
                value={direction}
                onChange={async (event, value) => {
                  await motorService.setDirection(value);
                  setMotorDirection(value);
                }}
                exclusive
                aria-label="text alignment"
              >
                <ToggleButton value="CCW" aria-label="left aligned">
                  <RotateLeftIcon />
                </ToggleButton>
                <ToggleButton value="CW" aria-label="right aligned">
                  <RotateRightIcon />
                </ToggleButton>
              </ToggleButtonGroup>
            </div>

            <div className="direction-buttons">
              <Button
                variant="contained"
                color="secondary"
                onClick={async () => {
                  await motorService.deleteRevolutions();
                  setCWRevolutions(0);
                  setCCWRevolutions(0);
                }}
              >
                Clear Revolution Count
              </Button>
            </div>
          </div>
        </>
      ) : null}
    </div>
  );
}

export default App;
