import "./info-param.scss";

function InfoParam({ title, value }) {
  return (
    <div className="info-param">
      <div className="info-title">{title}</div>
      <div className="info-value">{value}</div>
    </div>
  );
}

export default InfoParam;
