const express = require('express');
const cors = require('cors');

const routes = require('./routes.js');

// ***************************************************************************************
// server settings
const app = express();
const PORT = process.env.PORT || 9000;
const corsOptions = { origin: 'http://localhost:3000', credentials: true, optionSucessStatus: 200 }

app.listen(PORT, () => {console.log(`server started running on port ${PORT}`)});
app.use(express.json());
app.use(cors(corsOptions));
app.use('/', routes);